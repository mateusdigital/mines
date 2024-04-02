//~---------------------------------------------------------------------------//
//                               *       +                                    //
//                         '                  |                               //
//                     ()    .-.,="``"=.    - o -                             //
//                           '=/_       \     |                               //
//                        *   |  '=._    |                                    //
//                             \     `=./`,        '                          //
//                          .   '=.__.=' `='      *                           //
//                 +                         +                                //
//                      O      *        '       .                             //
//                                                                            //
//  File      : game_cursor.c                                                 //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//


#ifndef __GAME_CURSOR__
#define __GAME_CURSOR__

//------------------------------------------------------------------------------
#include "mdgb/mdgb.h"
//
#include "game_defs.h"
#include "globals.h"
//
#include "game_cursor.h"
#include "game_background.h"
#include "Field.h"


// -----------------------------------------------------------------------------
#define _CURSOR_TILE_INDEX_TOP_LEFT     0x04
#define _CURSOR_TILE_INDEX_TOP_RIGHT    0x05
#define _CURSOR_TILE_INDEX_BOTTOM_LEFT  0x14
#define _CURSOR_TILE_INDEX_BOTTOM_RIGHT 0x15

// -----------------------------------------------------------------------------
#define CURSOR_MIN_X 0
#define CURSOR_MAX_X 9

#define CURSOR_MIN_Y 0
#define CURSOR_MAX_Y 7

// -----------------------------------------------------------------------------
i8 CursorX;
i8 CursorY;


//------------------------------------------------------------------------------
void _move_cur()
{
    u8 x = CursorX * TILE_SIZE_x2 + FIRST_PIXEL_X;
    u8 y = CursorY * TILE_SIZE_x2 + FIRST_PIXEL_Y;

    move_sprite(CURSOR_SPRITE_INDEX + 0, x            , y);
    move_sprite(CURSOR_SPRITE_INDEX + 1, x + TILE_SIZE, y);
    move_sprite(CURSOR_SPRITE_INDEX + 2, x            , y + TILE_SIZE);
    move_sprite(CURSOR_SPRITE_INDEX + 3, x + TILE_SIZE, y + TILE_SIZE);
}

//
// Public Functions
//

//------------------------------------------------------------------------------
void game_cursor_init()
{
    set_sprite_tile(CURSOR_SPRITE_INDEX + 0, _CURSOR_TILE_INDEX_TOP_LEFT);
    set_sprite_tile(CURSOR_SPRITE_INDEX + 1, _CURSOR_TILE_INDEX_TOP_RIGHT);
    set_sprite_tile(CURSOR_SPRITE_INDEX + 2, _CURSOR_TILE_INDEX_BOTTOM_LEFT);
    set_sprite_tile(CURSOR_SPRITE_INDEX + 3, _CURSOR_TILE_INDEX_BOTTOM_RIGHT);

    _move_cur();
}

//------------------------------------------------------------------------------
void game_cursor_update()
{
    if(JUST_PRESSED(J_LEFT)) {
        --CursorX;
    }
    if(JUST_PRESSED(J_RIGHT)) {
        ++CursorX;
    }
    if(JUST_PRESSED(J_UP)) {
        --CursorY;
    }
    if(JUST_PRESSED(J_DOWN)) {
        ++CursorY;
    }

    if(CursorX > CURSOR_MAX_X) {
        BackgroundOffsetX += 1;
        CursorX            = CURSOR_MAX_X;
    }
    else if(CursorX < CURSOR_MIN_X) {
        BackgroundOffsetX -= 1;
        CursorX            = CURSOR_MIN_X;
    }

    if(CursorY > CURSOR_MAX_Y) {
        BackgroundOffsetY += 1;
        CursorY            = CURSOR_MAX_Y;
    }
    else if(CursorY < CURSOR_MIN_Y) {
        BackgroundOffsetY -= 1;
        CursorY            = CURSOR_MIN_Y;
    }

    BackgroundOffsetX = Clamp(BackgroundOffsetX, 0, FieldCols - CURSOR_MAX_X);
    BackgroundOffsetY = Clamp(BackgroundOffsetY, 0, FieldRows - CURSOR_MAX_Y);

    // printf("%d %d\n", BackgroundOffsetX, BackgroundOffsetY);
    _move_cur();
}

#endif // __GAME_CURSOR__