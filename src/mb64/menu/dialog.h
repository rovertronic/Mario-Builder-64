#pragma once

#include "engine.h"

extern MatrixComponent *gCurDialog;
extern int gDialogResponse;

void create_dialog_box(char *dialog);
void create_dialog_box_with_response(char *dialog, void (*response)(int));
void create_badge_dialog(int badgeid);
void begin_badge_dialog_close(void);
