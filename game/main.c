// mcow_gb
#include "mcow_gb/mcow_gb.c"
// Resources
#include "tiles/tiles.c"
// Entities
#include "objects/field.c"
#include "objects/background.c"
#include "objects/breaking_block.c"
#include "objects/cursor.c"
// UI
#include "ui/game_hud.c"
// Screens
#include "screen/screens.c"
#include "screen/screen_game.c"

//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
GameInit()
{
    disable_interrupts();
    DISPLAY_OFF;

    SPRITES_8x8;

    SHOW_BKG;
    SHOW_SPRITES;

    DISPLAY_ON;
    enable_interrupts();
}


//----------------------------------------------------------------------------//
// Entry Point                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
main()
{
    Screen_Change(SCREEN_TYPE_GAME);
    // Screen_Change(SCREEN_TYPE_SPLASH);

    while(1) {
        Screen_Update();
    }
}
