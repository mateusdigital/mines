#include <gb/gb.h>
#include <stdint.h>

#include "resources/game_tiles_tiles.h"
#include "resources/game_tiles_tiles.c"
// #include "resources/game_tiles_map.h"
#include "resources/game_tiles_map.c"
#include "resources/MenuMap.h"
#include "resources/MenuMap.c"

#include "resources/TestMap.h"
#include "resources/TestMap.c"
void main(void)
{
    // Load tileset into GB memory
     // Load the tile data into VRAM
     // Fill entire screen with 1st tile
    init_bkg(0);
    set_bkg_data(0, game_tiles_tiles_count, game_tiles_tiles);
    // set_bkg_tiles(0, 0, MenuMap_WIDTH, MenuMap_HEIGHT, MenuMap_TILES);
    set_bkg_tiles(0, 0, TestMap_WIDTH, TestMap_HEIGHT, TestMap_TILES);

    // set_bkg_tiles(0, 0, game_tiles_map_width, game_tiles_map_height, game_tiles_map);


    // Show background
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    move_sprite(0, 50, 50);
    move_sprite(1, 50, 50);
    while (1)
    {
        //   scroll_bkg(1, 0);
        delay(200);
    }
}
