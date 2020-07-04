// Header
#include "screen_game.h"
// Game
#include "game_defs.h"
#include "objects/field.h"
#include "objects/background.h"
#include "objects/cursor.h"
#include "objects/breaking_block.h"
#include "ui/game_hud.h"

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
#define GAME_STATE_SELECTING      1
#define GAME_STATE_ANIMATING_OPEN 2
#define GAME_STATE_ANIMATING_BOMB 3


#define GAME_SCREEN_FRAMES_BETWEEN_HAPPY_AND_NORMA_FACE 80


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
U8  GameState;
U8  GameTimer;
U16 GameScore;


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
    set_bkg_data   (0, 128, TILES_OBJECTS);

    GameState  = GAME_STATE_SELECTING;
    GameTimer  = 0;
    GameScore  = 0;

    FieldRows  = FIELD_MAX_ROWS;
    FieldCols  = FIELD_MAX_COLS;
    MinesCount = 3;

    //
    // Init the Game subsystems...
    Random_Init(4);

    Field_Init         ();
    Bkg_Init           ();
    Cursor_Init        ();
    BreakingBlocks_Init();
    GameHud_Init       ();

    //
    // Setup the Hud.
    GameHud_SetMinesCount(MinesCount);
    GameHud_SetTimerCount(GameTimer );
    GameHud_SetScoreCount(GameScore );
    GameHud_Refresh();

    //
    // Setup the cursor.
    Cursor_Show();

    SHOW_WIN;
    SHOW_BKG;
    SHOW_SPRITES;
    VBK_REG = 0;
}

//------------------------------------------------------------------------------
void
Game_Update()
{
    U8 _delay;
    U8 _frames;

    Input_Reset();

    _delay  = 0;
    _frames = 0;

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
                    goto END_OF_FRAME; // @notice(stdmatt): First time in life that I used that...
                }

                // Opened blocks...
                //   Now check if the was a bomb or not.
                //   If was a bomb start the bomb opening animation
                //   otherwise start the blocks opening animation.
                if(HAS_BOMB(Field[Field_OpenIndices[0]])) {
                    GameState = GAME_STATE_ANIMATING_BOMB;
                    BreakingBlocks_Start(Field_OpenIndicesCount, TRUE);
                } else {
                    GameState = GAME_STATE_ANIMATING_OPEN;
                    BreakingBlocks_Start(Field_OpenIndicesCount, FALSE);
                }

                Cursor_Hide();
                GameHud_SetFaceState(GAME_HUD_FACE_STATE_WOW);
                Shake_Reset(
                    2, // frames per loop
                    0xff,
                    4, // max x
                    4  // max y
                );
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

                // Stop the breaking animation.
                BreakingBlocks_End  ();
                Shake_Stop          ();
                Bkg_ResetShakeOffset();

                // Make the little guy happy ;D
                GameHud_SetFaceStateTimed(
                    GAME_HUD_FACE_STATE_HAPPY,
                    GAME_SCREEN_FRAMES_BETWEEN_HAPPY_AND_NORMA_FACE,
                    GAME_HUD_FACE_STATE_NORMAL
                );

                // Re-enable the cursor.
                Cursor_Show();


                // Calculate the score.
                GameScore += (MinesCount * Field_OpenIndicesCount);
                GameHud_SetScoreCount(GameScore);
                GameHud_Refresh();
            }
        }

        //
        // Animating Bomb.
        else if(GameState == GAME_STATE_ANIMATING_BOMB) {
            BreakingBlocks_Update();
            Shake_Update         ();
            Bkg_UpdateShakeOffset();

            // Finished to animate all the opening blocks...
            if(BreakingBlocks_HasFinished()) {
                // Stop the breaking animation...
                BreakingBlocks_End  ();
                Shake_Stop          ();
                Bkg_ResetShakeOffset();

                // Make the little guy dead :'(
                GameHud_SetFaceState(GAME_HUD_FACE_STATE_DEAD);
            }
        }


END_OF_FAME:
        if(GameState == GAME_STATE_SELECTING && (++_frames >= 60)) {
            _frames = 0;
            ++GameTimer;
            GameHud_SetTimerCount(GameTimer);
            GameHud_Refresh();
        }

        GameHud_Update();
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
