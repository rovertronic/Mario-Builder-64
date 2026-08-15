#!/usr/bin/env python3
"""Compose button icons onto BGs and emit CI4/CI8 C arrays."""
import os
import sys

import png

FOLDERS = [
    ("folder_gentle_slopes", "lowergentle"),
    ("folder_slopes", "slope"),
    ("folder_platforms", "movingplatform"),
    ("folder_switches", "purpleswitch"),
    ("folder_boxes", "box"),
    ("folder_fire", "redflame"),
    ("folder_power_stars", "star"),
    ("folder_coins", "coin"),
    ("folder_powerups", "pipebar"),
    ("folder_npcs", "signpost"),
    ("folder_generic_enemies", "goomba"),
    ("folder_bullies", "bully"),
    ("folder_mechanical_enemies", "bobomb"),
    ("folder_misc_enemies", "scuttlebug"),
    ("folder_slabs", "slab"),
    ("folder_stone_enemies", "thwomp"),
    ("folder_flying_enemies", "lakitu"),
    ("folder_vanilla_bosses", "bowser"),
    ("folder_diagonal_slopes", "cornerslope"),
    ("folder_special_tiles", "water"),
    ("folder_btcm_enemies", "rex"),
    ("folder_btcm_bosses", "showrunner"),
]

STANDALONE = {"blank", "folderopen"}
SKIP_STEMS = {"folder", "outline.ia4"}
SIZE = 32
MAX_CI4 = 16
MAX_CI8 = 256


def load_rgba(path):
    w, h, rows, _info = png.Reader(path).asRGBA()
    if w != SIZE or h != SIZE:
        raise SystemExit("%s is %dx%d, expected %dx%d" % (path, w, h, SIZE, SIZE))
    pixels = []
    for row in rows:
        row = list(row)
        pixels.append([tuple(row[i:i + 4]) for i in range(0, len(row), 4)])
    return pixels


def over(dst, src):
    sa = src[3] / 255.0
    if sa <= 0.0:
        return dst
    if sa >= 1.0:
        return src
    da = dst[3] / 255.0
    out_a = sa + da * (1.0 - sa)
    if out_a <= 0.0:
        return (0, 0, 0, 0)
    inv = 1.0 - sa
    rgb = tuple(int(round((src[i] * sa + dst[i] * da * inv) / out_a)) for i in range(3))
    return (rgb[0], rgb[1], rgb[2], int(round(out_a * 255.0)))


def composite(bg, icon):
    out = [row[:] for row in bg]
    for y in range(SIZE):
        for x in range(SIZE):
            sx, sy = x + 1, y + 1
            if sx < SIZE and sy < SIZE and icon[sy][sx][3] == 0:
                out[sy][sx] = over(out[sy][sx], (0, 0, 0, icon[y][x][3] // 2))
    for y in range(SIZE):
        for x in range(SIZE):
            out[y][x] = over(out[y][x], icon[y][x])
    return out


def to_5551(p):
    r, g, b, a = p
    if a == 0:
        return 0
    return ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | 1


def unpack_rgb(c):
    return ((c >> 11) & 31, (c >> 6) & 31, (c >> 1) & 31)


def pack_rgb(rgb):
    r, g, b = rgb
    return (r << 11) | (g << 6) | (b << 1) | 1


def channel_range(pts, ch):
    lo = min(p[ch] for p in pts)
    hi = max(p[ch] for p in pts)
    return hi - lo


def median_cut(pts, ncolors):
    boxes = [list(pts)]
    while len(boxes) < ncolors:
        boxes.sort(key=lambda b: len(b) * (1 + max(channel_range(b, c) for c in range(3))), reverse=True)
        box = boxes[0]
        if len(box) < 2:
            break
        axis = max(range(3), key=lambda c: channel_range(box, c))
        box = sorted(boxes.pop(0), key=lambda p: p[axis])
        mid = max(1, len(box) // 2)
        boxes.append(box[:mid])
        boxes.append(box[mid:])
    pal = []
    for box in boxes:
        n = len(box)
        pal.append(tuple(sum(p[i] for p in box) // n for i in range(3)))
    return pal


def nearest(pal_rgb, c):
    pr, pg, pb = unpack_rgb(c)
    best, bd = 0, 1 << 30
    for i, (r, g, b) in enumerate(pal_rgb):
        d = (r - pr) ** 2 + (g - pg) ** 2 + (b - pb) ** 2
        if d < bd:
            best, bd = i, d
    return best


def make_ci(rgba):
    pix = [to_5551(rgba[y][x]) for y in range(SIZE) for x in range(SIZE)]
    has_t = any((c & 1) == 0 for c in pix)
    opaque = []
    seen = {}
    for c in pix:
        if (c & 1) == 0:
            continue
        if c not in seen:
            seen[c] = len(opaque)
            opaque.append(c)

    max_opaque = MAX_CI8 - (1 if has_t else 0)
    if len(opaque) > max_opaque:
        rgb_pts = [unpack_rgb(c) for c in pix if (c & 1)]
        pal_rgb = median_cut(rgb_pts, max_opaque)
        pal = ([0] if has_t else []) + [pack_rgb(c) for c in pal_rgb]
        t_off = 1 if has_t else 0
        idx = [0 if (c & 1) == 0 else t_off + nearest(pal_rgb, c) for c in pix]
    else:
        pal = ([0] if has_t else []) + opaque
        remap = {c: i for i, c in enumerate(pal)}
        # all transparent 5551 values collapse to index 0
        idx = [0 if (c & 1) == 0 else remap[c] for c in pix]

    ci4 = len(pal) <= MAX_CI4
    if ci4:
        tex = []
        for i in range(0, len(idx), 2):
            tex.append((idx[i] << 4) | idx[i + 1])
    else:
        tex = idx

    pal_bytes = []
    for c in pal:
        pal_bytes.append((c >> 8) & 0xFF)
        pal_bytes.append(c & 0xFF)
    return ci4, tex, pal_bytes


def emit_bytes(data):
    lines = []
    for i in range(0, len(data), 32):
        lines.append("".join("0x%02X," % b for b in data[i:i + 32]))
    return "\n".join(lines)


def emit_button(out, stem, rgba):
    ci4, tex, pal = make_ci(rgba)
    name = "mb64_btn_" + stem
    fmt = "ci4" if ci4 else "ci8"
    macro = "DEFINE_CI4_BUTTON" if ci4 else "DEFINE_CI8_BUTTON"
    out.write("ALIGNED8 static const Texture %s_%s[] = {\n%s\n};\n" % (name, fmt, emit_bytes(tex)))
    out.write("ALIGNED8 static const Texture %s_pal_rgba16[] = {\n%s\n};\n" % (name, emit_bytes(pal)))
    out.write("%s(%s);\n\n" % (macro, name))


def png_path(srcdir, stem):
    return os.path.join(srcdir, stem + ".png")


def main():
    if len(sys.argv) != 3:
        raise SystemExit("usage: compose_buttons.py <srcdir> <outfile>")
    srcdir, outfile = sys.argv[1], sys.argv[2]

    blank = load_rgba(png_path(srcdir, "blank"))
    folder = load_rgba(png_path(srcdir, "folder"))
    cache = {"blank": blank, "folder": folder}

    def get(stem):
        if stem not in cache:
            cache[stem] = load_rgba(png_path(srcdir, stem))
        return cache[stem]

    stems = []
    for fname in sorted(os.listdir(srcdir)):
        if not fname.endswith(".png"):
            continue
        stem = fname[:-4]
        if stem in SKIP_STEMS:
            continue
        stems.append(stem)

    tmp = outfile + ".tmp"
    os.makedirs(os.path.dirname(outfile), exist_ok=True)
    with open(tmp, "w") as out:
        out.write("/* generated by tools/compose_buttons.py - do not edit */\n\n")
        for stem in stems:
            rgba = get(stem) if stem in STANDALONE else composite(blank, get(stem))
            emit_button(out, stem, rgba)
        for out_stem, icon_stem in FOLDERS:
            emit_button(out, out_stem, composite(folder, get(icon_stem)))
    os.replace(tmp, outfile)


if __name__ == "__main__":
    main()
