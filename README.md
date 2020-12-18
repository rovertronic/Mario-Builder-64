# S2DEX Text Engine

## How to "Install"
- Clone this repo into a folder in your SM64 decomp or homebrew repo
- Include that folder in your makefile's `SRC_DIRS`
- Add that folder to the linker script (`sm64.ld`) or specfile
- You're ready to use S2DEX Text Engine!

## Usage (Sample Program)
```c
#include "s2d_engine/init.h"
#include "s2d_engine/s2d_draw.h"
#include "s2d_engine/s2d_print.h"

char myString[] = "This is a " SCALE "2" "test string!\n"
                "Supports a bunch of standard " ROTATE "-36" "escape characters!\n"
                "\tIncluding " COLOR "255 0 0 0" "Colorful text!";

// ...
void some_func(void) {
	uObjMtx *buffer;
	// substitute with a different alloc function as neccesary
	buffer = alloc_display_list(0x200 * sizeof(uObjMtx));
	s2d_print(50, 50, myString, buffer);
}
```


## Command Usage
(All numbers must be in base 10)
- `SCALE "N"` - Scales text N times (Can be negative)
- `ROTATE "N"` - Rotates each glyph by N degrees (Can be negative, useful for italics)
- `TRANSLATE "X Y"` - Moves the rest of the string to the specified X and Y position
- `COLOR "R G B A"` - Sets the text color to the specified value
