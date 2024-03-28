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

#include "game_defs.h"
#include "globals.h"

#include "ui/hud.h"
#include "objects/game_cursor.h"
#include "objects/game_background.h"

//
// Constants
//

// -----------------------------------------------------------------------------

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
void game_screen_init()
{
    curr_screen_func = &game_screen_draw;

    game_background_init();
    game_cursor_init    ();
    hud_init            ();
}

//------------------------------------------------------------------------------
void game_screen_draw()
{
    game_cursor_draw();
    hud_draw();
}

//
// Private Functions Definitions
//
//------------------------------------------------------------------------------

#endif // __GAME_SCREEN__