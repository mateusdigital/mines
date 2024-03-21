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
//  File      : main.c                                                        //
//  Project   : mines                                                         //
//  Date      : 2024-03-20                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

//
// mdgb
//

// -----------------------------------------------------------------------------
#include "mdgb.h"


//
// Tile Data
//

// -----------------------------------------------------------------------------
#include "resources/game_tiles_tiles.h"
#include "resources/game_tiles_tiles.c"


//
// Map Data
//

//------------------------------------------------------------------------------
#include "resources/MenuMap.h"
#include "resources/MenuMap.c"

#include "resources/TestMap.h"
#include "resources/TestMap.c"

#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
const char* LEVEL_STRS[3] = { "EASY", "MEDIUM", "HARD"};

#define TILE_INDEX_BLANK           0x0f

#define TILE_INDEX_LETTERS_UPPER_A 0x30

#define TILE_INDEX_ARROWS_DARK     0x90
#define TILE_INDEX_ARROWS_LIGHT    0x94
#define TILE_OFFSET_ARROWS_UP      0
#define TILE_OFFSET_ARROWS_LEFT    1
#define TILE_OFFSET_ARROWS_DOWN    2
#define TILE_OFFSET_ARROWS_RIGHT   3

#define TILE_INDEX_HEART_DARK  0x0E
#define TILE_INDEX_HEART_LIGHT 0x1E

//------------------------------------------------------------------------------
u8 current_level_index = 2;
u8 prev_level_last_tile_index = 0;
bool draw_level_arrows = false;

u8 last_input;
u8 input;


//
//
//

// -----------------------------------------------------------------------------
void draw_level()
{
    for(u8 i = 0; i < prev_level_last_tile_index; ++i) {
        move_sprite(i, 0, 0);
    }

    prev_level_last_tile_index = 0;

    // Arrows
    const u8 left_arrow_tile_index = (current_level_index == 0 || !draw_level_arrows)
        ? TILE_INDEX_BLANK
        : TILE_INDEX_ARROWS_LIGHT + TILE_OFFSET_ARROWS_LEFT;

    const u8 right_arrow_tile_index = (current_level_index == 2 || !draw_level_arrows)
        ? TILE_INDEX_BLANK
        : TILE_INDEX_ARROWS_LIGHT + TILE_OFFSET_ARROWS_RIGHT;

    set_sprite_tile(prev_level_last_tile_index++, left_arrow_tile_index);
    set_sprite_tile(prev_level_last_tile_index++, right_arrow_tile_index);

    // Text
    u8 const *str     = LEVEL_STRS[current_level_index];
    u8 const  str_len = strlen(str);

    u8 const pos_y = FIRST_PIXEL_Y + 60;
    u8       pos_x = (((SCREEN_WIDTH_IN_TILES >> 1) - ((str_len) >> 1)) << TILE_SIZE_SHIFT);

    move_sprite(0, pos_x, pos_y);
    pos_x += TILE_SIZE;

    for(u8 i = 0; i < str_len; ++i) {
        set_sprite_tile(prev_level_last_tile_index, TILE_INDEX_LETTERS_UPPER_A + str[i] - 'A');
        move_sprite    (prev_level_last_tile_index, pos_x, pos_y);

        pos_x += TILE_SIZE;
        ++prev_level_last_tile_index;
    }

    move_sprite(1, pos_x, pos_y);
}

void draw_credits()
{
    set_sprite_tile(0, TILE_INDEX_HEART_LIGHT);
    move_sprite(0, 6 * TILE_SIZE + FIRST_PIXEL_X, 10 * TILE_SIZE + FIRST_PIXEL_Y);

}


#define JUST_PRESSED(J) ((J & last_input) == 0 && (input & J))

//
// Entry Point
//

// -----------------------------------------------------------------------------
void main(void)
{
    set_bkg_data(0, game_tiles_tiles_count, game_tiles_tiles);
    set_sprite_data(0, 128, game_tiles_tiles);

    set_bkg_tiles(0, 0, MenuMap_WIDTH, MenuMap_HEIGHT, MenuMap_TILES);
    // set_bkg_tiles(0, 0, TestMap_WIDTH, TestMap_HEIGHT, TestMap_TILES);


    // Show background
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    draw_level();
    while (1)
    {
        last_input = input;
        input      = joypad();

        // J_START, J_SELECT, J_A, J_B, J_UP, J_DOWN, J_LEFT, J_RIGHT
        if(JUST_PRESSED(J_LEFT) && draw_level_arrows) {
            if(current_level_index > 0) {
                --current_level_index;
                draw_level();
            }
        }
        else if(JUST_PRESSED(J_RIGHT) && draw_level_arrows) {
            if(current_level_index < 2) {
                ++current_level_index;
                draw_level();
            }
        }

        if(JUST_PRESSED(J_DOWN)) {
            draw_level_arrows = false;
            draw_level();
            draw_credits();
        }
        else if(JUST_PRESSED(J_UP)) {
            draw_level_arrows = true;
            draw_credits();
            draw_level();
        }
    }
}
