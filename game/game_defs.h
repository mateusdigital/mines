#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__

// mcow
#include "mcow_gb/mcow_gb.h"


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

#define _PRINT_INFO 1

#endif // __GAME_DEFS_H__
