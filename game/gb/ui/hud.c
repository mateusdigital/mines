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
//  File      : hud.c                                                         //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#ifndef __HUD_C__
#define __HUD_C__

//------------------------------------------------------------------------------
#include "hud.h"

#include "game_defs.h"
#include "globals.h"
#include "resources/HudWin.h"

//
// Constants
//

// -----------------------------------------------------------------------------
#define _TIME_WIN_X  4
#define _MINES_WIN_X 9
#define _SCORE_WIN_X 15

//
// Private Vars
//

//------------------------------------------------------------------------------


//
// Private Functions Declarations
//

//------------------------------------------------------------------------------


//
// Public functions
//

// -----------------------------------------------------------------------------
void hud_init()
{
    set_win_tiles(0,0, HudWin_WIDTH, HudWin_HEIGHT, HudWin_TILES);
    move_win(FIRST_PIXEL_X -1, SCREEN_HEIGHT - HudWin_HEIGHT * TILE_SIZE);

    SHOW_WIN;

    hud_set_time (0);
    hud_set_mines(0);
    hud_set_score(0);
}

//------------------------------------------------------------------------------
void hud_draw()
{

}

//------------------------------------------------------------------------------
void hud_set_time(u16 time)
{
    set_win_tile_xy(_TIME_WIN_X + 0, 1, TILE_INDEX_NUMBER_0 + ((time / 100)));
    set_win_tile_xy(_TIME_WIN_X + 1, 1, TILE_INDEX_NUMBER_0 + ((time % 100) / 10));
    set_win_tile_xy(_TIME_WIN_X + 2, 1, TILE_INDEX_NUMBER_0 + ((time % 100) % 10));
}

//------------------------------------------------------------------------------
void hud_set_mines(u16 mines)
{
    set_win_tile_xy(_MINES_WIN_X + 0, 1, TILE_INDEX_NUMBER_0 + ((mines / 100)));
    set_win_tile_xy(_MINES_WIN_X + 1, 1, TILE_INDEX_NUMBER_0 + ((mines % 100) / 10));
    set_win_tile_xy(_MINES_WIN_X + 2, 1, TILE_INDEX_NUMBER_0 + ((mines % 100) % 10));
}

//------------------------------------------------------------------------------
void hud_set_score(u16 score)
{
    set_win_tile_xy(_SCORE_WIN_X + 0, 1, TILE_INDEX_NUMBER_0 + (score / 1000));
    set_win_tile_xy(_SCORE_WIN_X + 1, 1, TILE_INDEX_NUMBER_0 + ((score / 100) % 10));
    set_win_tile_xy(_SCORE_WIN_X + 2, 1, TILE_INDEX_NUMBER_0 + ((score / 10) % 10));
    set_win_tile_xy(_SCORE_WIN_X + 3, 1, TILE_INDEX_NUMBER_0 + (score % 10));
}



//
// Private Functions Definitions
//

//------------------------------------------------------------------------------

#endif // __HUD_C__