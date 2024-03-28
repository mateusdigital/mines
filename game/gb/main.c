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
//  File      : main.c                                                        //
//  Project   : mines                                                         //
//  Date      : 2024-03-20                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

//
// mdgb
//

// -----------------------------------------------------------------------------
#include "mdgb/mdgb.h"
#include "mdgb/mdgb.c"

//
// Tile Data
//

// -----------------------------------------------------------------------------
#include "resources/game_tiles_tiles.h"
#include "resources/game_tiles_tiles.c"


//
// Map Data
//

//------------------------------------------------------------------------------
#include "resources/TestMap.h"
#include "resources/TestMap.c"

#include "resources/MenuMap.h"
#include "resources/MenuMap.c"

#include "resources/CreditsMap.h"
#include "resources/CreditsMap.c"

#include "resources/HudWin.h"
#include "resources/HudWin.c"

#include "globals.h"
#include "globals.c"

#include "screens/menu_screen.h"
#include "screens/menu_screen.c"

#include "ui/hud.h"
#include "ui/hud.c"

#include "objects/game_background.h"
#include "objects/game_background.c"

#include "objects/game_cursor.h"
#include "objects/game_cursor.c"

#include "screens/game_screen.h"
#include "screens/game_screen.c"

//------------------------------------------------------------------------------

//
// Entry Point
//

// -----------------------------------------------------------------------------
void main(void)
{
    set_bkg_data   (0, game_tiles_tiles_count, game_tiles_tiles);
    set_win_data   (0, game_tiles_tiles_count, game_tiles_tiles);
    set_sprite_data(0, game_tiles_tiles_count, game_tiles_tiles);

    SHOW_BKG;
    SHOW_SPRITES;
    // SHOW_WIN;

    DISPLAY_ON;

    game_screen_init();
    while (1)
    {
        UPDATE_INPUT();
        curr_screen_func();

        wait_vbl_done();
    }
}
