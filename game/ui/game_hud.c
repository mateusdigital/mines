// Header
#include "ui/game_hud.h"

#define GAME_HUD_TIME_DIGIT_2 24
#define GAME_HUD_TIME_DIGIT_1 25
#define GAME_HUD_TIME_DIGIT_0 26

#define GAME_HUD_MINES_DIGIT_1 30
#define GAME_HUD_MINES_DIGIT_0 31

#define GAME_HUD_SCORE_DIGIT_3 35
#define GAME_HUD_SCORE_DIGIT_2 36
#define GAME_HUD_SCORE_DIGIT_1 37
#define GAME_HUD_SCORE_DIGIT_0 38

#define GAME_HUD_FACE_TL 13
#define GAME_HUD_FACE_TR 14
#define GAME_HUD_FACE_BL 33
#define GAME_HUD_FACE_BR 34

#define GAME_HUD_MAX_SCORE_COUNT 9999
#define GAME_HUD_MAX_TIMER_COUNT 999
#define GAME_HUD_MAX_MINES_COUNT 99

#define TILE_ID_DIGIT_0 116
#define TILE_ID_GAME_HUD_FACE_FIRST 60


U8 _GameHud_FaceAnimTime;
U8 _GameHud_IsAnimating;
U8 _GameHud_FinalState;

void
GameHud_Init()
{
    move_win(7, 144 - TILE_SIZE_x2);

    GameHud_SetTimerCount(999);
    GameHud_SetMinesCount(999);
    GameHud_SetScoreCount(9999);
    GameHud_SetFaceState(GAME_HUD_FACE_STATE_NORMAL);

    _GameHud_FaceAnimTime = 0;
    _GameHud_IsAnimating  = FALSE;
    _GameHud_FinalState   = 0;

    GameHud_Refresh();
}

void
GameHud_Refresh()
{
    set_win_tiles(0, 0, 20, 2, MAP_GAME_HUD);
}

void
GameHud_Update()
{
    if(!_GameHud_IsAnimating) {
        return;
    }
    --_GameHud_FaceAnimTime;
    if(_GameHud_FaceAnimTime == 0) {
        GameHud_SetFaceState(_GameHud_FinalState);
        _GameHud_IsAnimating = FALSE;
    }
}

void
GameHud_SetMinesCount(U8 count)
{
    if(count > GAME_HUD_MAX_MINES_COUNT) {
        count = GAME_HUD_MAX_MINES_COUNT;
    }

    MAP_GAME_HUD[GAME_HUD_MINES_DIGIT_1] = TILE_ID_DIGIT_0 + ((count % 100) / 10);
    MAP_GAME_HUD[GAME_HUD_MINES_DIGIT_0] = TILE_ID_DIGIT_0 + ((count % 100) % 10);
}

void
GameHud_SetTimerCount(U16 count)
{
    if(count > GAME_HUD_MAX_TIMER_COUNT) {
        count = GAME_HUD_MAX_TIMER_COUNT;
    }

    MAP_GAME_HUD[GAME_HUD_TIME_DIGIT_2] = TILE_ID_DIGIT_0 + (count / 100);
    MAP_GAME_HUD[GAME_HUD_TIME_DIGIT_1] = TILE_ID_DIGIT_0 + ((count % 100) / 10);
    MAP_GAME_HUD[GAME_HUD_TIME_DIGIT_0] = TILE_ID_DIGIT_0 + ((count % 100) % 10);
}

void
GameHud_SetScoreCount(U16 count)
{
    if(count > GAME_HUD_MAX_SCORE_COUNT) {
        count = GAME_HUD_MAX_SCORE_COUNT;
    }

    MAP_GAME_HUD[GAME_HUD_SCORE_DIGIT_3] = TILE_ID_DIGIT_0 + (((count / 1000)      )     );
    MAP_GAME_HUD[GAME_HUD_SCORE_DIGIT_2] = TILE_ID_DIGIT_0 + (((count / 1000) % 100)     );
    MAP_GAME_HUD[GAME_HUD_SCORE_DIGIT_1] = TILE_ID_DIGIT_0 + (((count % 1000) % 100) / 10);
    MAP_GAME_HUD[GAME_HUD_SCORE_DIGIT_0] = TILE_ID_DIGIT_0 + (((count % 1000) % 100) % 10);
}

void
GameHud_SetFaceState(U8 state)
{
    state = (state * 4);
    MAP_GAME_HUD[GAME_HUD_FACE_TL] = (TILE_ID_GAME_HUD_FACE_FIRST + state) + 0;
    MAP_GAME_HUD[GAME_HUD_FACE_BL] = (TILE_ID_GAME_HUD_FACE_FIRST + state) + 1;
    MAP_GAME_HUD[GAME_HUD_FACE_TR] = (TILE_ID_GAME_HUD_FACE_FIRST + state) + 2;
    MAP_GAME_HUD[GAME_HUD_FACE_BR] = (TILE_ID_GAME_HUD_FACE_FIRST + state) + 3;

    GameHud_Refresh();
}



void
GameHud_SetFaceStateTimed(U8 first_state, U8 frames_count, U8 final_state)
{
    _GameHud_IsAnimating  = TRUE;
    _GameHud_FaceAnimTime = frames_count;
    _GameHud_FinalState  = final_state;

    GameHud_SetFaceState(first_state);
}
