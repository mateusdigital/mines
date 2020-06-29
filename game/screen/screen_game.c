// Header
#include "screen_game.h"
// Game
#include "game_defs.h"

//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
typedef struct Tile_Tag {
    U8 x;
    U8 y;

    U8 id;
} Tile_t;


Tile_t tile;

// 0000 0000
// |||| Number of mines
// |||| 0 - 15
// ||||
// ||||_ 1 - is open.
// |||__ 1 - is flag.
// ||___ 1 - has bomb.
// |____ 0 - unused.
#define MASK_OPEN  (0x10)
#define MASK_FLAG  (0x20)
#define MASK_BOMB  (0x40)
#define MASK_VALUE (0x0F)

#define HAS_BOMB(_byte_)    (((_byte_) & MASK_BOMB)  != 0)
#define IS_OPENED(_byte_)   (((_byte_) & MASK_OPEN)  != 0)
#define IS_FLAGGED(_byte_)  (((_byte_) & MASK_FLAG)  != 0)
#define MINES_VALUE(_byte_) (((_byte_) & MASK_VALUE)     )


#define SET_OPEN(_byte_)    ((_byte_) | MASK_OPEN)
#define TOGGLE_FLAG(_byte_) ((_byte_) ^ MASK_FLAG)

U8 BackgroundTiles[20 * 18] = {0};
U8 Field[9 * 10]            = {0};
U8 FieldCols;
U8 FieldRows;
U8 MinesCount;

#define TILE_ID_FLAG  10
#define TILE_ID_OPEN   1
#define TILE_ID_CLOSE  0
#define TILE_ID_BOMB  12


#define BIG_TILE_ID(_id_) (_id_ * 4)

void
Bkg_SetTile(U8 field_y, U8 field_x)
{
    U8 field_index;
    U8 field_value;

    U16 tile_index;
    U8 tile_id;

    field_index = field_x + (field_y * 10);
    field_value = Field[field_index];

    tile_index = (U16)(field_x * 2) + (U16)field_y * 2 * (U16)20;
    if(HAS_BOMB(field_value)) {
        tile_id = TILE_ID_BOMB;
    }

    else if(IS_FLAGGED(field_value)) {
        tile_id = TILE_ID_FLAG;
    } else if(IS_OPENED(field_value)) {
        tile_id = (TILE_ID_OPEN + MINES_VALUE(field_value));
    } else {
        tile_id = TILE_ID_CLOSE;
    }

    tile_id = BIG_TILE_ID(tile_id);
    BackgroundTiles[tile_index     ] = tile_id + 0;  // Top    Left.
    BackgroundTiles[tile_index + 20] = tile_id + 1;  // Bottom Left.
    BackgroundTiles[tile_index +  1] = tile_id + 2;  // Top    Right.
    BackgroundTiles[tile_index + 21] = tile_id + 3;  // Bottom Right.
}

void
Bkg_Refresh()
{

    U8 i, j;
    for(i = 0; i < 9; ++i) {
        for(j = 0; j < 10; ++j) {
            Bkg_SetTile(i, j);
        }
    }
    set_bkg_tiles(0, 0, 20, 18, BackgroundTiles);
}


void
Field_BumpMines(I8 y, I8 x)
{
    I8 i, j;
    for(i = -1; i <= +1; ++i) {
        if(i + y < 0 || i + y >= FieldRows) {
            continue;
        }

        for(j = -1; j <= +1; ++j) {
            if(j + x < 0 || j + x >= FieldCols) {
                continue;
            }
            if((i + y) == y && (j + x) == x) {
                Field[x + y * FieldCols] |= MASK_BOMB;
            }

            ++Field[(j + x) + ((i + y) * FieldCols)];
        }
    }
}

void
Field_PlaceMines()
{

    U8 i, j;
    U8 index;
    U8 mines_count;

    index       = 0;
    mines_count = MinesCount;

    for(i = 0; i < FieldRows; ++i) {
        for(j = 0; j < FieldCols; ++j) {
            Field[index] = 0;
            Field[index] |= MASK_OPEN;
            ++index;
        }
    }

    while(mines_count > 0) {
        i = Random_U8(0, FieldRows);
        j = Random_U8(0, FieldCols);

        index = j + (i * FieldCols);
        if(HAS_BOMB(Field[index])) {
            continue;
        }

        Field[index] |= MASK_BOMB;
        Field_BumpMines(i, j);

        --mines_count;
    }
}


//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
Game_Init()
{

    VBK_REG = 1;
    HIDE_SPRITES;
    HIDE_BKG;

    FieldRows  = 9;
    FieldCols  = 10;
    MinesCount = 5;
    set_sprite_data(0, 128, TILES_OBJECTS);
    tile.x = 0;
    tile.y = 0;

    // Field[0] = SET_OPEN(Field[0]);
    // Field[1] = TOGGLE_FLAG(Field[1]);


    move_bkg(0, 0);
    set_bkg_data(0, 128, TILES_OBJECTS);


            Random_Init(DIV_REG);

            Field_PlaceMines();
            Bkg_Refresh();
    SHOW_BKG;
    // SHOW_SPRITES;
    VBK_REG = 0;
}

//------------------------------------------------------------------------------
void
Game_Update()
{
    U8 _delay;

    Input_Reset();
    _delay = 1;


    while(1) {
        Input_BeginFrame();
        if(JOY_CLICK(J_LEFT)) {
            tile.y -= 1;

        } else if(JOY_CLICK(J_RIGHT)) {
            tile.y += 1;

        }

        if(JOY_CLICK(J_UP)) {
            tile.y -= 1;

        } else if(JOY_CLICK(J_DOWN)) {
            tile.y += 1;

        }

        if(JOY_CLICK(J_A)) {
            Random_Init(DIV_REG);

            Field_PlaceMines();
            Bkg_Refresh();
        }

        Input_EndFrame();

        // Refresh
        Delay(_delay);
        wait_vbl_done();
    }
}

//------------------------------------------------------------------------------
void
Game_Quit()
{
    // Empty...
}
