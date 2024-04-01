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
#include "mdgb/mdgb.h"
#include "globals.h"
#include "game_background.h"


//------------------------------------------------------------------------------
void game_background_init()
{
    u8 field_cols = 16;
    u8 field_rows = 16;

    for(u8 row = 0; row < field_rows; ++row) {
        u8 row2 = row * 2;
        for(u8 col = 0; col < field_cols; ++col) {
            u8 col2 = col * 2;

            set_bkg_tile_xy(col2    , row2    , 0x00);
            set_bkg_tile_xy(col2 + 1, row2    , 0x01);
            set_bkg_tile_xy(col2    , row2 + 1, 0x10);
            set_bkg_tile_xy(col2 + 1, row2 + 1, 0x11);

            // BackgroundTiles[tile_index     ] = tile_id + 0;  // Top    Left.
            // BackgroundTiles[tile_index + 20] = tile_id + 1;  // Bottom Left.
            // BackgroundTiles[tile_index +  1] = tile_id + 2;  // Top    Right.
            // BackgroundTiles[tile_index + 21] = tile_id + 3;  // Bottom Right
        }
    }
}
// -----------------------------------------------------------------------------
void game_background_set_offset(i8 offset_x, i8 offset_y)
{
    move_bkg(offset_x * TILE_SIZE_x2, offset_y * TILE_SIZE_x2);
}

#endif // __GAME_BACKGROUND_C__