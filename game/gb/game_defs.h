//~---------------------------------------------------------------------------//
//                               *       +                                    //
//                         '                  |                               //
//                     ()    .-.,="``"=.    - o -                             //
//                           '=/_       \     |                               //
//                        *   |  '=._    |                                    //
//                             \     `=./`,        '                          //
//                          .   '=.__.=' `='      *                           //
//                 +                         +                                //
//                      O      *        '       .                             //
//                                                                            //
//  File      : game_defs.h                                                   //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__

//
// Screen
//

//------------------------------------------------------------------------------
#define SCREEN_TYPE_SPLASH  0
#define SCREEN_TYPE_MENU    1
#define SCREEN_TYPE_GAME    2
#define SCREEN_TYPE_CREDITS 2

//
// Level
//

//------------------------------------------------------------------------------
#define LEVEL_INDEX_EASY   0
#define LEVEL_INDEX_MEDIUM 1
#define LEVEL_INDEX_HARD   2

//
// Cursor
//

//------------------------------------------------------------------------------
#define CURSOR_BLINK_FRAMES_COUNT 0x8
#define CURSOR_SPRITE_INDEX 0
#define CURSOR_SPRITE_COUNT 4

//
// Explosion
//

// -----------------------------------------------------------------------------
#define EXPLOSION_SPRITE_INDEX CURSOR_SPRITE_COUNT
#define EXPLOSION_SPRITE_COUNT 4



//
// Field
//

// -----------------------------------------------------------------------------
#define FIELD_MAX_ROWS 14
#define FIELD_MAX_COLS 15
#define FIELD_ARRAY_SIZE (FIELD_MAX_ROWS * FIELD_MAX_COLS)

//
// Tiles
//

//------------------------------------------------------------------------------
#define TILE_INDEX_BLANK           0x0f

#define TILE_INDEX_LETTERS_UPPER_A  0x30
#define TILE_INDEX_NUMBER_0         0xA0

#define TILE_INDEX_ARROWS_DARK     0x90
#define TILE_INDEX_ARROWS_LIGHT    0x94
#define TILE_OFFSET_ARROWS_UP      0
#define TILE_OFFSET_ARROWS_LEFT    1
#define TILE_OFFSET_ARROWS_DOWN    2
#define TILE_OFFSET_ARROWS_RIGHT   3

#define TILE_INDEX_HEART_DARK  0x0E
#define TILE_INDEX_HEART_LIGHT 0x1E


#define TILE_INDEX_BLOCK_TL 0x00
#define TILE_INDEX_BLOCK_TR 0x01
#define TILE_INDEX_BLOCK_BL 0x10
#define TILE_INDEX_BLOCK_BR 0x11

#define TILE_INDEX_BLOCK_OPEN_TL 0x02
#define TILE_INDEX_BLOCK_OPEN_TR 0x03
#define TILE_INDEX_BLOCK_OPEN_BL 0x12
#define TILE_INDEX_BLOCK_OPEN_BR 0x13

#define TILE_INDEX_BLOCK_OPEN_BL_0 0x20

//------------------------------------------------------------------------------
#define CHAR_TO_TILE(C) (TILE_INDEX_LETTERS_UPPER_A + C - 'A')


#endif // __GAME_DEFS_H__
