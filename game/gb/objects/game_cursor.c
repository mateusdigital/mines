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
#include "mdgb.h"
#include "globals.h"
#include "game_cursor.h"

u8 _cursor_x = 0;
u8 _cursor_y = 0;

#define _CURSOR_TILE_INDEX 0
#define _CURSOR_SPR_INDEX_TOP_LEFT     0x04
#define _CURSOR_SPR_INDEX_TOP_RIGHT    0x05
#define _CURSOR_SPR_INDEX_BOTTOM_LEFT  0x14
#define _CURSOR_SPR_INDEX_BOTTOM_RIGHT 0x15

void _move_cur()
{
    u8 x = _cursor_x * TILE_SIZE_x2 + FIRST_PIXEL_X;
    u8 y = _cursor_y * TILE_SIZE_x2 + FIRST_PIXEL_Y;

    move_sprite(_CURSOR_TILE_INDEX + 0, x            , y);
    move_sprite(_CURSOR_TILE_INDEX + 1, x + TILE_SIZE, y);
    move_sprite(_CURSOR_TILE_INDEX + 2, x            , y+ TILE_SIZE);
    move_sprite(_CURSOR_TILE_INDEX + 3, x + TILE_SIZE, y+ TILE_SIZE);
}

//
// Public Functions
//

//------------------------------------------------------------------------------
void game_cursor_init()
{
    set_sprite_tile(_CURSOR_TILE_INDEX + 0, _CURSOR_SPR_INDEX_TOP_LEFT);
    set_sprite_tile(_CURSOR_TILE_INDEX + 1, _CURSOR_SPR_INDEX_TOP_RIGHT);
    set_sprite_tile(_CURSOR_TILE_INDEX + 2, _CURSOR_SPR_INDEX_BOTTOM_LEFT);
    set_sprite_tile(_CURSOR_TILE_INDEX + 3, _CURSOR_SPR_INDEX_BOTTOM_RIGHT);

    _move_cur();
}

//------------------------------------------------------------------------------
void game_cursor_draw()
{
    if(JUST_PRESSED(J_LEFT)) {
        --_cursor_x;
    }
    if(JUST_PRESSED(J_RIGHT)) {
        ++_cursor_x;
    }
    if(JUST_PRESSED(J_UP)) {
        --_cursor_y;
    }
    if(JUST_PRESSED(J_DOWN)) {
        ++_cursor_y;
    }
    if(_cursor_x > 9) {
        move_bkg(- (_cursor_x % 9) * TILE_SIZE_x2, 0);
    }
    _move_cur();
}

#endif // __GAME_CURSOR__