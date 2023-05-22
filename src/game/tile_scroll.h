#include "types.h"

#define PACK_TILESIZE(w, d) ((w << 2) + d)

typedef struct {
    int cmd:8;
    int s:12;
    int t:12;
    int pad:4;
    int i:4;
    int u:12;
    int v:12;
} SetTileSize;

void shift_s(Gfx *dl, u32 cmd, u16 s);
void shift_t(Gfx *dl, u32 cmd, u16 t);
void shift_s_down(Gfx *dl, u32 cmd, u16 s);
void shift_t_down(Gfx *dl, u32 cmd, u16 t);

