// Header
#include "screen_game.h"
// Game
#include "game_defs.h"
#include "objects/field.h"
#include "objects/background.h"


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
typedef struct Tile_Tag {
    U8 x;
    U8 y;

    U8 id;
} Tile_t;



//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
Game_Init()
{
    VBK_REG = 1;
    HIDE_SPRITES;
    HIDE_BKG;

    FieldRows  = FIELD_MAX_ROWS;
    FieldCols  = FIELD_MAX_COLS;
    MinesCount = 5;

    set_sprite_data(0, 128, TILES_OBJECTS);

    // Field[0] = SET_OPEN(Field[0]);
    // Field[1] = TOGGLE_FLAG(Field[1]);

    Random_Init(DIV_REG);

    Field_Init();
    Bkg_Init  ();


    SHOW_BKG;
    // SHOW_SPRITES;
    VBK_REG = 0;
}

//------------------------------------------------------------------------------
void
Game_Update()
{
    U8 _delay;

    Input_Reset();
    _delay = 1;


    while(1) {
        Input_BeginFrame();

        //
        // Movement...
        // if(JOY_CLICK(J_LEFT)) {
        // } else if(JOY_CLICK(J_RIGHT)) {
        // } else if(JOY_CLICK(J_UP)) {
        // } else if(JOY_CLICK(J_DOWN)) {
        // }

        //
        // Action
        // if(JOY_CLICK(J_A)) {

        // } else if(JOY_CLICK(J_B)) {

        // }

        //
        // View mode.
        // if(JOY_CLICK(J_SELECT)) {
//
        // }

        Input_EndFrame();

        //
        // Refresh
        Delay(_delay);
        wait_vbl_done();
    }
}

//------------------------------------------------------------------------------
void
Game_Quit()
{
    // Empty...
}
