// Header
#include "objects/field.h"

//----------------------------------------------------------------------------//
// MACROS                                                                     //
//----------------------------------------------------------------------------//
#define FIELD_INDEX(y, x) (x + y * FIELD_MAX_COLS)


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
// Public
U8 Field[FIELD_ARRAY_SIZE] = {0};

U8 FieldCols;
U8 FieldRows;
U8 MinesCount;

// Private
U8 _flood_fill_indices[FIELD_ARRAY_SIZE];


//----------------------------------------------------------------------------//
// Private Functions                                                          //
//----------------------------------------------------------------------------//
void
_Field_PlaceMine(I8 y, I8 x)
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

//------------------------------------------------------------------------------
void
_Field_PlaceMines()
{
    U8 i, j;
    U8 index;
    U8 mines_count;

    //
    // Reset the array.
    // @optimize(stdmatt): We just need to go to the FieldRows * FieldCols.
    for(index = 0; index < FIELD_ARRAY_SIZE; ++index) {
        Field[index] = 0;
    }
    //
    // Place the Bombs...
    mines_count = MinesCount;
    while(mines_count > 0) {
        i = Random_U8(0, FieldRows);
        j = Random_U8(0, FieldCols);

        index = j + (i * FieldCols);
        if(HAS_BOMB(Field[index])) {
            continue;
        }

        //printf("Placing mine %d %d\n", i, j);
        Field[index] |= MASK_BOMB;
        _Field_PlaceMine(i, j);

        --mines_count;
    }
}

//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
Field_Init()
{
    _Field_PlaceMines();
}


//------------------------------------------------------------------------------
void
_FieldPrint(U8 p)
{
    U8 index;
    U8 i, j;
    U8 field_value;

    gprintxy(0, 0, "Priting... %d %d\n", FIELD_MAX_ROWS, FIELD_MAX_COLS);
    for(i = 0; i < FIELD_MAX_ROWS; ++i) {
        for(j = 0; j < FIELD_MAX_COLS; ++j) {
            field_value = Field[FIELD_INDEX(i, j)];
            if(HAS_BOMB(field_value)) {
                gprintxy(j, i, "*");
            }
            else if(IS_FLAGGED(field_value)) {
                gprintxy(j, i, "F");
            } else if(p || IS_OPENED(field_value)) {
                gprintxy(j, i, "%c", '0' + MINES_VALUE(field_value));
                //  '0' + MINES_VALUE(field_value);
            } else {
                gprintxy(j, i, ".");
            }
        }
    }
}

U8 flood_fill_indices_count;
U8 flood_fill_indices_index;
//------------------------------------------------------------------------------
U8
Field_Open(I8 y, I8 x)
{
    I8 i;
    I8 j;

    I8 index;
    I8 xx;
    I8 yy;

    flood_fill_indices_count = 0;
    flood_fill_indices_index = 0;

    //
    // Check if the position is good to be opened.
    index = FIELD_INDEX(y, x);
    if(IS_OPENED(Field[index])) {
        #if _PRINT_INFO
            gprintxy(0, 12, "Already open: %d %d", y, x);
        #endif // _PRINT_INFO
        return FIELD_OPEN_RET_NONE;
    } else if(IS_FLAGGED(Field[index])) {
        #if _PRINT_INFO
            gprintxy(0, 12, "Flagged: %d %d", y, x);
        #endif // _PRINT_INFO
        return FIELD_OPEN_RET_NONE;
    } else if(HAS_BOMB(Field[index])) {
        return FIELD_OPEN_RET_BOMB;
    }

    y = 0;
    x = 0;
    xx = 0;
    yy = 0;

    //
    // Reset the flood fill vars.
    flood_fill_indices_count = 1;
    flood_fill_indices_index = 0;
    _flood_fill_indices[0]   = index;


    // _FieldPrint(1);
    while(flood_fill_indices_index < flood_fill_indices_count) {
        index = _flood_fill_indices[flood_fill_indices_index];
        ++flood_fill_indices_index;

        if(IS_FLAGGED(Field[index])) {
            continue;
        }
        SET_OPEN(Field[index]);

        x = (index % FieldCols);
        y = (index / FieldCols);
        for(i = -1; i <= +1; ++i) {
            yy = (i + y);

            // gprintxy(5, 5, "...........");
            // gprintxy(5, 5, "i: %d y: %d", i, yy);
            // Out of bounds...
            if((yy < 0)|| (yy >= FIELD_MAX_ROWS)) {
                continue;
            }
            for(j = -1; j <= +1; ++j) {
                xx = (j + x);

                // gprintxy(5, 6, "...........");
                // gprintxy(5, 6, "j: %d x: %d ", j, xx);

                // Out of bounds...
                if((xx < 0) || (xx >= FIELD_MAX_COLS)) {
                    continue;
                }

                // gprintxy(5, 8, "  %d (%d) %d (%d)   ", yy, i,  xx, j);
                index = FIELD_INDEX(yy, xx);
                // waitpad(J_A);

                // Already participated on the flood fill algorithm.
                if((Field[index] & MASK_FLOOD_FILL) != 0) {
                    continue;
                }
                Field[index] |= MASK_FLOOD_FILL;

                // Has surrounding bombs...
                if(MINES_VALUE(Field[index]) != 0) {
                    if(!IS_FLAGGED(Field[index])) {
                        SET_OPEN(Field[index]);
                    }
                    continue;
                }

                _flood_fill_indices[flood_fill_indices_count] = index;
                ++flood_fill_indices_count;
            }
        }
    }

    return flood_fill_indices_count;
}

//------------------------------------------------------------------------------
void
Field_ToggleFlag(I8 y, I8 x)
{
    I8 index = FIELD_INDEX(y, x);
    if(IS_OPENED(Field[index])) {
        return;
    }
    TOGGLE_FLAG(Field[index]);
}
