#ifndef __BREAKING_BLOCK_H__
#define __BREAKING_BLOCK_H__

// Game
#include "game_defs.h"



void BreakingBlocks_Init ();
void BreakingBlocks_Reset();

void BreakingBlocks_Start      (U8 count);
BOOL BreakingBlocks_HasFinished();
void BreakingBlocks_End        ();
#endif // __BREAKING_BLOCK_H__
