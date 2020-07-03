// Header
#include "screen_game.h"
// Game
#include "game_defs.h"
#include "objects/field.h"
#include "objects/background.h"
#include "objects/cursor.h"
#include "objects/breaking_block.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
#define GAME_STATE_SELECTING      1
#define GAME_STATE_ANIMATING_OPEN 2
#define GAME_STATE_ANIMATING_BOMB 3


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
U8 GameState;
U8 FieldOpenReturnValue;

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

    set_sprite_data(0, 128, TILES_OBJECTS);

    GameState  = GAME_STATE_SELECTING;
    FieldRows  = FIELD_MAX_ROWS;
    FieldCols  = FIELD_MAX_COLS;
    MinesCount = 3;

    Random_Init(4);

    Field_Init         ();
    Bkg_Init           ();
    Cursor_Init        ();
    BreakingBlocks_Init();

    SHOW_BKG;
    SHOW_SPRITES;
    VBK_REG = 0;
}

//------------------------------------------------------------------------------
void
Game_Update()
{
    U8 _delay;
    Input_Reset();
    _delay = 0;

    while(1) {
        Input_BeginFrame();

        //
        // Selecting
        if(GameState == GAME_STATE_SELECTING) {
            Cursor_Update();
            //
            // Open.
            if(JOY_CLICK(J_A)) {
                Field_ToOpenY = ((Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2);
                Field_ToOpenX = ((Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2);

                // Didn't opened nothing...
                if(!Field_FindIndicesToOpen()) {
                    goto END_OF_FRAME;
                }

                // Opened blocks...
                //   Now check if the was a bomb or not.
                //   If was a bomb start the bomb opening animation
                //   otherwise start the blocks opening animation.
                if(HAS_BOMB(Field[Field_OpenIndices[0]])) {
                    GameState = GAME_STATE_ANIMATING_BOMB;
                } else {
                    GameState = GAME_STATE_ANIMATING_OPEN;

                    BreakingBlocks_Start(Field_OpenIndicesCount);
                    Shake_Reset(
                        2, // frames per loop
                        0xFF, // @TODO(stdmatt): Remove magic numbers...
                        4, // max x
                        4  // max y
                    );
                }
            }
            //
            // Flag
            else if(JOY_CLICK(J_B)) {
                Field_ToggleFlag(
                    (Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2,
                    (Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2
                );
            }
        }
        //
        // Animating Open.
        else if(GameState == GAME_STATE_ANIMATING_OPEN) {
            BreakingBlocks_Update();
            Shake_Update         ();
            Bkg_UpdateShakeOffset();

            // Finished to animate all the opening blocks...
            if(BreakingBlocks_HasFinished()) {
                GameState = GAME_STATE_SELECTING;
                BreakingBlocks_End  ();
                Bkg_ResetShakeOffset();
            }
        }

        //
        // Animating Bomb.
        else if(FieldOpenReturnValue == GAME_STATE_ANIMATING_BOMB) {
        }


END_OF_FRAME:
        Input_EndFrame();
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
