#ifndef __GAME_HUD_H__
#define __GAME_HUD_H__


#define GAME_HUD_FACE_STATE_NORMAL 0
#define GAME_HUD_FACE_STATE_WOW    1
#define GAME_HUD_FACE_STATE_HAPPY  2
#define GAME_HUD_FACE_STATE_DEAD   3


void GameHud_Init();
void GameHud_Refresh();
void GameHud_Update();

void GameHud_SetMinesCount(U8 count);
void GameHud_SetTimerCount(U16 count);
void GameHud_SetScoreCount(U16 count);


void GameHud_SetFaceState(U8 state);
void GameHud_SetFaceStateTimed(U8 first_state, U8 frames_count, U8 final_state);

#endif // __GAME_HUD_H__
