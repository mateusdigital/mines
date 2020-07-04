#ifndef __CURSOR_H__
#define __CURSOR_H__

// Game
#include "game_defs.h"


typedef struct Cursor_Tag {
    U8 x;
    U8 y;

    U8 blink_frame;
} Cursor_t;

extern Cursor_t Cursor;


void Cursor_Init  ();
void Cursor_Update();

void Cursor_Show();
void Cursor_Hide();

#endif //__CURSOR_H__
