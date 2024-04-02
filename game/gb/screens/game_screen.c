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
//  File      : game_screen.c                                                 //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#ifndef __GAME_SCREEN_C__
#define __GAME_SCREEN_C__

//------------------------------------------------------------------------------
#include "screens/game_screen.h"
//
#include "game_defs.h"
#include "globals.h"
//
#include "ui/hud.h"
#include "objects/game_cursor.h"
#include "objects/game_background.h"
//
#include "Field.h"

//
// Constants
//

// -----------------------------------------------------------------------------

//
// Private Vars
//

//------------------------------------------------------------------------------


//
// Private Functions
//

//------------------------------------------------------------------------------
void _try_to_open_block()
{
    //game_background_open_tile_xy(CursorX, CursorY);


    const u8 index = Field_OpenIndices[0];
    u8 col, row;
    Field_IndexToXY(index, &col, &row);

    u8 x = (col * TILE_SIZE_x2 + FIRST_PIXEL_X);
    u8 y = (row * TILE_SIZE_x2 + FIRST_PIXEL_Y);

    set_sprite_tile(EXPLOSION_SPRITE_INDEX + 0, TILE_INDEX_ARROWS_DARK + TILE_OFFSET_ARROWS_UP); //TILE_INDEX_BLOCK_TL);
    set_sprite_tile(EXPLOSION_SPRITE_INDEX + 1, TILE_INDEX_ARROWS_DARK + TILE_OFFSET_ARROWS_LEFT); //TILE_INDEX_BLOCK_TR);
    set_sprite_tile(EXPLOSION_SPRITE_INDEX + 2, TILE_INDEX_ARROWS_DARK + TILE_OFFSET_ARROWS_DOWN); //TILE_INDEX_BLOCK_BL);
    set_sprite_tile(EXPLOSION_SPRITE_INDEX + 3, TILE_INDEX_ARROWS_DARK + TILE_OFFSET_ARROWS_RIGHT); //TILE_INDEX_BLOCK_BR);


    move_sprite(EXPLOSION_SPRITE_INDEX + 0, x             , y);
    move_sprite(EXPLOSION_SPRITE_INDEX + 1,     x + TILE_SIZE , y);
    move_sprite(EXPLOSION_SPRITE_INDEX + 2, x             , y + TILE_SIZE);
    move_sprite(EXPLOSION_SPRITE_INDEX + 3, x + TILE_SIZE , y + TILE_SIZE);

    bool opened_something = Field_FindIndicesToOpen(CursorX, CursorY);
    if(!opened_something) {
        return;
    }

    // Field_OpenIndicesCount

}

//
// Public functions
//

// -----------------------------------------------------------------------------
void game_screen_init()
{
    curr_screen_func = &game_screen_update;

    Field_Init(FIELD_MAX_ROWS, FIELD_MAX_COLS, 10);

    game_background_init();
    game_cursor_init    ();
    hud_init            ();
}

//------------------------------------------------------------------------------
void game_screen_update()
{
    game_cursor_update    ();
    game_background_update();
    hud_update            ();

    if(JUST_PRESSED(J_A)) {
        _try_to_open_block();
    }
}

//
// Private Functions Definitions
//
//------------------------------------------------------------------------------

#endif // __GAME_SCREEN__