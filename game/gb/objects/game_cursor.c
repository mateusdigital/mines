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
#include "game_defs.h"
#include "globals.h"
#include "game_cursor.h"
#include "game_background.h"


// -----------------------------------------------------------------------------
#define _CURSOR_TILE_INDEX 0
#define _CURSOR_SPR_INDEX_TOP_LEFT     0x04
#define _CURSOR_SPR_INDEX_TOP_RIGHT    0x05
#define _CURSOR_SPR_INDEX_BOTTOM_LEFT  0x14
#define _CURSOR_SPR_INDEX_BOTTOM_RIGHT 0x15

// -----------------------------------------------------------------------------
#define CURSOR_MIN_X 0
#define CURSOR_MAX_X 9

#define CURSOR_MIN_Y 0
#define CURSOR_MAX_Y 7

// -----------------------------------------------------------------------------
i8 _cursor_x = 0;
i8 _cursor_y = 0;

i8 _background_offset_x = 0;
i8 _background_offset_y = 0;


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

    if(_cursor_x > CURSOR_MAX_X) {
        _background_offset_x += 1;
        _cursor_x             = CURSOR_MAX_X;
    }
    else if(_cursor_x < CURSOR_MIN_X) {
        _background_offset_x -= 1;
        _cursor_x             = CURSOR_MIN_X;
    }

    if(_cursor_y > CURSOR_MAX_Y) {
        _background_offset_y += 1;
        _cursor_y             = CURSOR_MAX_Y;
    }
    else if(_cursor_y < CURSOR_MIN_Y) {
        _background_offset_y -= 1;
        _cursor_y             = CURSOR_MIN_Y;
    }

    _background_offset_x = Clamp(_background_offset_x, 0, FIELD_MAX_COLS - CURSOR_MAX_X);
    _background_offset_y = Clamp(_background_offset_y, 0, FIELD_MAX_ROWS - CURSOR_MAX_Y);


    // printf("%d %d\n", _background_offset_x, _background_offset_y);
    game_background_set_offset(_background_offset_x, _background_offset_y);
    _move_cur();
}

#endif // __GAME_CURSOR__