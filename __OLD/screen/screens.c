// Game
#include "game_defs.h"
#include "screen_game.h"


//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
Screen_Change(U8 s)
{
    if(s == SCREEN_TYPE_SPLASH) {
    } else if(s == SCREEN_TYPE_GAME) {
        Game_Init  ();
        Screen_RunFunc = Game_Update;
    }
}
