#ifndef __BREAKING_BLOCK_H__
#define __BREAKING_BLOCK_H__

// Game
#include "game_defs.h"


typedef struct BreakingBlock_Tag {
    U8 x;
    U8 y;

    U8 blink_frame;
    U8 animation_time;
} BreakingBlock_t;

extern BreakingBlock_t BreakingBlock;

void BreakingBlock_Init();
void BreakingBlock_Reset();
void BreakingBlock_SetTilePos(U8 y, U8 x);
void BreakingBlock_Update();

#endif // __BREAKING_BLOCK_H__
