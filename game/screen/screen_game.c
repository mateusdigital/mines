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
U8 FieldOpenReturnValue;
U8 FieldOpenAnimCurrIndex;
U8 GameState;


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

    Random_Init(DIV_REG);

    Field_Init        ();
    Bkg_Init          ();
    Cursor_Init       ();
    BreakingBlock_Init();

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
                FieldOpenReturnValue = Field_Open(
                    (Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2,
                    (Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2
                );
                Bkg_Refresh();

                // Hit a bomb :(
                if(FieldOpenReturnValue == FIELD_OPEN_RET_BOMB) {
                    GameState = GAME_STATE_ANIMATING_BOMB;
                }
                // No bomb - Possible multiple blocks to open...
                else if(FieldOpenReturnValue != FIELD_OPEN_RET_NONE) {
                    GameState              = GAME_STATE_ANIMATING_OPEN;
                    FieldOpenAnimCurrIndex = 0;

                    BreakingBlock_Reset();
                    BreakingBlock_SetTilePos(
                        _flood_fill_indices[FieldOpenAnimCurrIndex] / FieldCols,
                        _flood_fill_indices[FieldOpenAnimCurrIndex] % FieldCols
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
                Bkg_Refresh();
            }
        }
        //
        // Animating Open.
        else if(GameState == GAME_STATE_ANIMATING_OPEN) {
            // Finished to animate all the opening blocks...
            if(FieldOpenAnimCurrIndex == FieldOpenReturnValue) {
                GameState == GAME_STATE_SELECTING;
                continue;
            }

            BreakingBlock_Update();
            if(BreakingBlock.animation_time == 0) {
                BreakingBlock_Reset();
                BreakingBlock_SetTilePos(
                    _flood_fill_indices[FieldOpenAnimCurrIndex] / FieldCols,
                    _flood_fill_indices[FieldOpenAnimCurrIndex] % FieldCols
                );

                ++FieldOpenAnimCurrIndex;
            }

        }

        //
        // Animating Bomb.
        else if(FieldOpenReturnValue == FIELD_OPEN_RET_BOMB) {
        }

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
