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

//------------------------------------------------------------------------------
#define SCREEN_TYPE_SPLASH  0
#define SCREEN_TYPE_MENU    1
#define SCREEN_TYPE_GAME    2
#define SCREEN_TYPE_CREDITS 2

//------------------------------------------------------------------------------
#define LEVEL_INDEX_EASY   0
#define LEVEL_INDEX_MEDIUM 1
#define LEVEL_INDEX_HARD   2

//------------------------------------------------------------------------------
#define CURSOR_BLINK_FRAMES_COUNT 0x8


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

//------------------------------------------------------------------------------
#define CHAR_TO_TILE(C) (TILE_INDEX_LETTERS_UPPER_A + C - 'A')



#endif // __GAME_DEFS_H__
