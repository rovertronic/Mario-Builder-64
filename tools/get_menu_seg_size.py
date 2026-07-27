import os
import sys

preliminaryMapPath: str = sys.argv[1]
buildFolder: str = sys.argv[2]

with open(preliminaryMapPath) as mapFile:
    line: str
    for line in mapFile:
        if "MENU_SEG_SIZE" in line:
            tokens: list[str] = line.split()
            with open(f"{buildFolder}/menu_seg_size.txt", "w+") as outputFile:
                sz: int = int(tokens[0], 16)
                sz += 16
                sz &= 0xFFFFFFF0
                outputFile.write(f"MENU_SEG_SIZE = 0x{sz:X};\n")
                sys.exit(0)
