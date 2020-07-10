#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__

// pw
#include "pw_gb/pw_gb.h"


//----------------------------------------------------------------------------//
// Game Constants                                                             //
//----------------------------------------------------------------------------//
#define SCREEN_TYPE_SPLASH  0
#define SCREEN_TYPE_GAME    2

#define BACKGROUND_MAX_COLS     20
#define BACKGROUND_MAX_ROWS     18
#define BACKGROUND_TILES_COUNT 360 // 20w x 18h

#define FIELD_MAX_COLS  10
#define FIELD_MAX_ROWS   9
#define FIELD_ARRAY_SIZE   (FIELD_MAX_COLS * FIELD_MAX_ROWS)

#define _PRINT_INFO 0


#define CURSOR_BLINK_FRAMES_COUNT 0x8
#define CURSOR_TILE_NO_FIRST   52
#define CURSOR_TILE_NO_LAST    55
#define CURSOR_SPRITE_ID_FIRST  0
#define CURSOR_SPRITE_ID_LAST   3


//
//
//
#define BREAKING_BLOCKS_MAX_COUNT          4
#define BREAKING_BLOCKS_OPEN_COUNT         4
#define BREAKING_BLOCKS_BOMB_COUNT         1

#define BREAKING_BLOCK_ANIMATION_TIME_MIN 10
#define BREAKING_BLOCK_ANIMATION_TIME_MAX 20

#define BREAKING_BLOCK_TILE_NO_FIRST    0  // 56
#define BREAKING_BLOCK_TILE_NO_LAST     3  // 59
#define BREAKING_BLOCK_SPRITE_ID_FIRST  4
#define BREAKING_BLOCK_SPRITE_ID_LAST   7


#endif // __GAME_DEFS_H__
