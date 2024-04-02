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
//  File      : game_background.c                                             //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//


#ifndef __GAME_BACKGROUND_C__
#define __GAME_BACKGROUND_C__

//------------------------------------------------------------------------------
#include "game_background.h"
//
#include "mdgb/mdgb.h"
//
#include "globals.h"
//
#include "Field.h"

//------------------------------------------------------------------------------
i8 BackgroundOffsetX = 0;
i8 BackgroundOffsetY = 0;


//------------------------------------------------------------------------------
void _set_block_close_xy(u8 x, u8 y)
{
    x *= 2;
    y *= 2;

    set_bkg_tile_xy(x    , y    , TILE_INDEX_BLOCK_TL);
    set_bkg_tile_xy(x + 1, y    , TILE_INDEX_BLOCK_TR);
    set_bkg_tile_xy(x    , y + 1, TILE_INDEX_BLOCK_BL);
    set_bkg_tile_xy(x + 1, y + 1, TILE_INDEX_BLOCK_BR);
}

void _set_block_open_xy(u8 x, u8 y, u8 value)
{
    x *= 2;
    y *= 2;
    u8 mines_value = MINES_VALUE(value);
    u8 value_block_index = (mines_value == 0)
        ? TILE_INDEX_BLOCK_OPEN_BL
        : (TILE_INDEX_BLOCK_OPEN_BL_0 + mines_value);

    set_bkg_tile_xy(x    , y    , TILE_INDEX_BLOCK_OPEN_TL);
    set_bkg_tile_xy(x + 1, y    , TILE_INDEX_BLOCK_OPEN_TR);
    set_bkg_tile_xy(x    , y + 1, value_block_index);
    set_bkg_tile_xy(x + 1, y + 1, TILE_INDEX_BLOCK_OPEN_BR);
}

//------------------------------------------------------------------------------
void game_background_init()
{
    for(u8 row = 0; row < FieldRows; ++row) {
        for(u8 col = 0; col < FieldCols; ++col) {
            // _set_block_close_xy(col, row);
            _set_block_open_xy(col, row, Field_GetXY(col, row));
        }
    }
}


// -----------------------------------------------------------------------------
void game_background_update()
{
    move_bkg(BackgroundOffsetX * TILE_SIZE_x2, BackgroundOffsetY * TILE_SIZE_x2);
}


// -----------------------------------------------------------------------------
void game_background_open_tile_xy(u8 x, u8 y)
{
    _set_block_open_xy(x, y, Field_GetXY(x, y));
}

#endif // __GAME_BACKGROUND_C__