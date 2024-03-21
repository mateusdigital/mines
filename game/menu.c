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
//  File      : menu.c                                                        //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//


#ifndef __MENU_C__
#define __MENU_C__

//------------------------------------------------------------------------------
#include "menu.h"

#include "game_defs.h"
#include "globals.h"
#include "resources/MenuMap.h"

//
// Constants
//

// -----------------------------------------------------------------------------
#define _LEFT_ARROW_SPR_INDEX  0
#define _RIGHT_ARROW_SPR_INDEX 1
#define _HEART_SPR_INDEX       2

#define _CREDITS_STR_SPR_INDEX (_HEART_SPR_INDEX + 1)
#define _CREDITS_STR_SPR_COUNT (7)

#define _LEVEL_STR_SPR_INDEX   (_CREDITS_STR_SPR_INDEX + _CREDITS_STR_SPR_COUNT)
#define _LEVEL_STR_SPR_COUNT   8

#define _TIME_TO_BLINK      128
#define _TIME_TO_BLINK_INCR 6

//
// Private Vars
//

//------------------------------------------------------------------------------
static const char* LEVEL_STRS[3] = { "EASY", "MEDIUM", "HARD"};
bool _selecting_level = true; // If false, we are selecting the credits...


u8 _left_tile  = 0;
u8 _right_tile = 0;
u8 _heart_tile = 0;

u8 _blink_time = 0;


//
// Private Functions Declarations
//

//------------------------------------------------------------------------------
void _draw_level  ();
void _draw_credits();
void _update_icons();


//
// Public functions
//

// -----------------------------------------------------------------------------
void menu_init()
{
    curr_screen_func = &menu_draw;

    set_bkg_tiles(0, 0, MenuMap_WIDTH, MenuMap_HEIGHT, MenuMap_TILES);
    move_bkg(0, 0);

    _draw_level  ();
    _draw_credits();
}

//------------------------------------------------------------------------------
void menu_draw()
{
    if(_selecting_level && JUST_PRESSED(J_LEFT)) {
        if(curr_level > 0) {
            --curr_level;
            _draw_level();
        }
    }
    else if(_selecting_level && JUST_PRESSED(J_RIGHT)) {
        if(curr_level < 2) {
            ++curr_level;
            _draw_level();
        }
    }

    if(JUST_PRESSED(J_DOWN)) {
        _selecting_level = false;
    }
    else if(JUST_PRESSED(J_UP)) {
        _selecting_level = true;
    }

    _update_icons();
    _blink_time += _TIME_TO_BLINK_INCR;
}

//
// Private Functions Definitions
//

// -----------------------------------------------------------------------------
void _draw_level()
{
    // Text
    u8 const *str       = LEVEL_STRS[curr_level];
    u8 const  str_len   = strlen(str);
    u8 const  leftovers = _LEVEL_STR_SPR_COUNT - str_len;

    u8 const pos_y = FIRST_PIXEL_Y + 60;
    u8       pos_x = (((SCREEN_WIDTH_IN_TILES >> 1) - ((str_len) >> 1)) << TILE_SIZE_SHIFT);

    move_sprite(_LEFT_ARROW_SPR_INDEX, pos_x, pos_y);
    pos_x += TILE_SIZE;

    for(u8 i = 0; i < str_len; ++i) {
        set_sprite_tile(_LEVEL_STR_SPR_INDEX + i, CHAR_TO_TILE(str[i]));
        move_sprite    (_LEVEL_STR_SPR_INDEX + i, pos_x, pos_y);

        pos_x += TILE_SIZE;
    }

    for(u8 i = str_len; i < str_len + leftovers; ++i) {
        set_sprite_tile(_LEVEL_STR_SPR_INDEX + i, TILE_INDEX_BLANK);
    }

    move_sprite(_RIGHT_ARROW_SPR_INDEX, pos_x, pos_y);
}

// -----------------------------------------------------------------------------
void _draw_credits()
{
    // Text
    u8 const *str     = "CREDITS";
    u8 const  str_len = strlen(str);

    u8 const pos_y = FIRST_PIXEL_Y + 80;
    u8       pos_x = (((SCREEN_WIDTH_IN_TILES >> 1) - ((str_len) >> 1)) << TILE_SIZE_SHIFT);

    move_sprite(_HEART_SPR_INDEX, pos_x, pos_y);
    pos_x += TILE_SIZE;

    for(u8 i = 0; i < str_len; ++i) {
        set_sprite_tile(_CREDITS_STR_SPR_INDEX + i, CHAR_TO_TILE(str[i]));
        move_sprite    (_CREDITS_STR_SPR_INDEX + i, pos_x, pos_y);

        pos_x += TILE_SIZE;
    }
}


//------------------------------------------------------------------------------
void _update_icons()
{
    _left_tile  = TILE_INDEX_BLANK;
    _right_tile = TILE_INDEX_BLANK;
    _heart_tile = TILE_INDEX_BLANK;

    // Arrows
    if(_selecting_level) {
        u8 _arrow_type = (_blink_time < _TIME_TO_BLINK) ? TILE_INDEX_ARROWS_LIGHT : TILE_INDEX_ARROWS_DARK;
        if(curr_level != 0) {
            _left_tile = _arrow_type + TILE_OFFSET_ARROWS_LEFT;
        }
        if(curr_level != 2) {
            _right_tile = _arrow_type + TILE_OFFSET_ARROWS_RIGHT;
        }
    }
    else {
        _heart_tile = (_blink_time < _TIME_TO_BLINK) ? TILE_INDEX_HEART_LIGHT : TILE_INDEX_HEART_DARK;
    }

    set_sprite_tile(_LEFT_ARROW_SPR_INDEX,  _left_tile);
    set_sprite_tile(_RIGHT_ARROW_SPR_INDEX, _right_tile);
    set_sprite_tile(_HEART_SPR_INDEX,       _heart_tile);
}


#endif // __MENU_C__