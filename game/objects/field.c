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

U8 Field_OpenIndicesCount;
// Private
U8 Field_OpenIndices[FIELD_ARRAY_SIZE];
U8 flood_fill_indices_index;

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


//------------------------------------------------------------------------------
BOOL
Field_FindIndicesToOpen()
{
    I8 i;
    I8 j;

    I8 index;
    I8 xx;
    I8 yy;

    index = FIELD_INDEX(Field_ToOpenY, Field_ToOpenX);

    //
    // Reset the indices that were opened.
    Field_OpenIndicesCount   = 1;     // Always open at least one
    flood_fill_indices_index = 0;     // Start from the beginning.
    Field_OpenIndices[0]     = index; // Actually if is already open it will return false...


    #if _PRINT_INFO
        gprintxy(0, 14, "---xxx : %d", (I16)Field_ToOpenY);
        gprintxy(0, 15, "---xxx : %d", (I16)Field_ToOpenX);
        gprintxy(0, 16, "---xxx : %d", index);
    #endif

    //
    // Check if the position is good to be opened.
    if(IS_OPENED(Field[index])) {
        #if _PRINT_INFO
            gprintxy(0, 15, "Value: %x", Field[index]);
            gprintxy(0, 12, "Already open: %d", Field_ToOpenY);
            gprintxy(0, 13, "Already open: %d", Field_ToOpenX);
        #endif // _PRINT_INFO
        return FALSE;
    } else if(IS_FLAGGED(Field[index])) {
        #if _PRINT_INFO
            gprintxy(0, 12, "Flagged: %d %d", Field_ToOpenY, Field_ToOpenX);
        #endif // _PRINT_INFO
        return FALSE;
    } else if(HAS_BOMB(Field[index])) {
        return TRUE;
    }

    Field_ToOpenY = 0;
    Field_ToOpenX = 0;
    xx = 0;
    yy = 0;

    // We start from with at least one index and while we find things
    // to open we continue to "push" things on the Field_OpenIndices array
    // the worst case is when there's no mines, so all the field will be opened.
    while(flood_fill_indices_index < Field_OpenIndicesCount) {
        index = Field_OpenIndices[flood_fill_indices_index];
        ++flood_fill_indices_index;

        if(IS_FLAGGED(Field[index])) {
            continue;
        }
        // SET_OPEN(Field[index]);

        // Tranform the index in X,Y coords again so it's easier to check
        // if the thing is inside the board bounds.
        Field_ToOpenX = (index % FieldCols);
        Field_ToOpenY = (index / FieldCols);
        for(i = -1; i <= +1; ++i) {
            yy = (i + Field_ToOpenY);

            // Out of bounds...
            if((yy < 0)|| (yy >= FIELD_MAX_ROWS)) {
                continue;
            }
            for(j = -1; j <= +1; ++j) {
                xx = (j + Field_ToOpenX);

                // Out of bounds...
                if((xx < 0) || (xx >= FIELD_MAX_COLS)) {
                    continue;
                }

                index = FIELD_INDEX(yy, xx);
                // Already participated on the flood fill algorithm.
                if((Field[index] & MASK_FLOOD_FILL) != 0) {
                    continue;
                }
                Field[index] |= MASK_FLOOD_FILL;

                // Has surrounding bombs...
                if(MINES_VALUE(Field[index]) != 0) {
                    continue;
                }

                Field_OpenIndices[Field_OpenIndicesCount] = index;
                ++Field_OpenIndicesCount;
            }
        }
    }

    for(i = 0; i < Field_OpenIndicesCount; ++i) {
        SET_OPEN(Field[Field_OpenIndices[i]]);
    }
    return TRUE;
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
