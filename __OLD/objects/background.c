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
    U8  tile_id;

    field_index = field_x + (field_y * FieldCols);
    field_value = Field[field_index];

    tile_index = (U16)(field_x * 2) + (U16)field_y * 2 * (U16)BACKGROUND_MAX_COLS;
    // if(HAS_BOMB(field_value)) {
    //     tile_id = TILE_ID_BOMB;
    // }
   if(IS_FLAGGED(field_value)) {
        tile_id = TILE_ID_FLAG;
    } else if(IS_OPENED(field_value)) {
        if(HAS_BOMB(field_value)) {
            tile_id = TILE_ID_BOMB;
        } else {
            tile_id = (TILE_ID_OPEN + MINES_VALUE(field_value));
        }
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
    U8 i, j;

    for(i = 0; i < FieldRows; ++i) {
        for(j = 0; j < FieldCols; ++j) {
            _Bkg_SetTile(i, j);
        }
    }
    Bkg_Refresh();
    move_bkg(0, 0);
}

//------------------------------------------------------------------------------
void
Bkg_Refresh()
{
    #if _PRINT_INFO
        _FieldPrint(0);
    #else
        set_bkg_tiles(0, 0, 20, 18, BackgroundTiles);
    #endif
}


//------------------------------------------------------------------------------
void
Bkg_UpdateShakeOffset()
{
    move_bkg(Shake_x, Shake_y);
}


//------------------------------------------------------------------------------
void
Bkg_ResetShakeOffset()
{
    move_bkg(0, 0);
}


void
Bkg_UpdateTile(U8 y, U8 x)
{

    _Bkg_SetTile(y, x);
    #if _PRINT_INFO
        _FieldPrint(1);
    #else
        _Bkg_SetTile(y, x);
        set_bkg_tiles(0, 0, 20, 18, BackgroundTiles);
    #endif // _PRINT_INFO
}
