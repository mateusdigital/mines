// Header
#include "objects/background.h"
// Game
#include "objects/field.h"

//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
// Public
U8 BackgroundTiles[BACKGROUND_TILES_COUNT];


//----------------------------------------------------------------------------//
// Private Functions                                                          //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
_Bkg_SetTile(U8 field_y, U8 field_x)
{
    U8 field_index;
    U8 field_value;

    U16 tile_index;
    U8 tile_id;

    field_index = field_x + (field_y * FieldCols);
    field_value = Field[field_index];

    tile_index = (U16)(field_x * 2) + (U16)field_y * 2 * (U16)BACKGROUND_MAX_COLS;
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


//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
Bkg_Init()
{
    set_bkg_data(0, 128, TILES_OBJECTS);
   Bkg_Refresh();

    move_bkg(0, 0);
}

//------------------------------------------------------------------------------
void
Bkg_Refresh()
{
    U8 i, j;
    for(i = 0; i < FieldRows; ++i) {
        for(j = 0; j < FieldCols; ++j) {
            _Bkg_SetTile(i, j);
        }
    }

    set_bkg_tiles(0, 0, 20, 18, BackgroundTiles);
}
