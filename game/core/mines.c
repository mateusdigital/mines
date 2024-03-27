// Header
#include "mines.h"

//----------------------------------------------------------------------------//
// MACROS                                                                     //
//----------------------------------------------------------------------------//
#define FIELD_INDEX(y, x) (x + y * FieldCols)


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
// Public
u8 Field[FIELD_ARRAY_SIZE] = {0};

u8 FieldCols;
u8 FieldRows;
u8 FieldMinesCount;

u8 Field_OpenIndicesCount;
// Private
u8 Field_OpenIndices[FIELD_ARRAY_SIZE];
u8 flood_fill_indices_index;


//
// Private Functions
//

// -----------------------------------------------------------------------------
void _Field_PlaceMine(u8 y, u8 x)
{
    i16 i, j;

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
void _Field_PlaceMines()
{
    u8 i, j;
    u8 index;
    u8 mines_count;

    //
    // Reset the array.
    // @optimize(mateusdigital): We just need to go to the FieldRows * FieldCols.
    for(index = 0; index < FIELD_ARRAY_SIZE; ++index) {
        Field[index] = 0;
    }

    //
    // Place the Bombs...
    mines_count = FieldMinesCount;
    while(mines_count > 0) {
        i = Rand_u8_ex(0, FieldRows);
        j = Rand_u8_ex(0, FieldCols);

        index = j + (i * FieldCols);
        if(HAS_BOMB(Field[index])) {
            continue;
        }

        flushprint("Placing mine %d %d\n", i, j);
        Field[index] |= MASK_BOMB;
        _Field_PlaceMine(i, j);

        --mines_count;
    }
}

// -----------------------------------------------------------------------------
void _Field_FindBombs()
{
    u8 i;

    flood_fill_indices_index = 0;
    for(i = 0; i < FIELD_ARRAY_SIZE; ++i) {
        if(HAS_BOMB(Field[i])) {
            Field_OpenIndices[flood_fill_indices_index] = i;
            ++flood_fill_indices_index;
        }
    }
    Field_OpenIndicesCount = FieldMinesCount;
}

// -----------------------------------------------------------------------------
void _Field_FindOpenBlocks(u8 x, u8 y)
{
    u8 index;
    i16 i;
    i16 j;

    i16 xx;
    i16 yy;

    // Reset the vars...
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

        // Transform the index in X,Y coords again so it's easier to check
        // if the thing is inside the board bounds.
        x = (index % FieldCols);
        y = (index / FieldCols);
        for(i = -1; i <= +1; ++i) {
            yy = (i + y);

            // Out of bounds...
            if((yy < 0)|| (yy >= FieldRows)) {
                continue;
            }
            for(j = -1; j <= +1; ++j) {
                xx = (j + x);

                // Out of bounds...
                if((xx < 0) || (xx >= FieldCols)) {
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
}


//
// Public Functions
//

// -----------------------------------------------------------------------------
void Field_Init(u8 rows, u8 cols, u8 minesCount)
{
    FieldRows       = rows;
    FieldCols       = cols;
    FieldMinesCount = minesCount;

    _Field_PlaceMines();
}


// -----------------------------------------------------------------------------
void Field_PrintDebug(bool showOpen)
{
    u8 i, j;
    u8 field_value;

    flushprint("Priting... %d %d\n", FieldRows, FieldRows);
    for(i = 0; i < FieldRows; ++i) {
        for(j = 0; j < FieldCols; ++j) {
            field_value = Field[FIELD_INDEX(i, j)];
            if(showOpen && HAS_BOMB(field_value)) {
                flushprint("*");
            }
            else if(IS_FLAGGED(field_value)) {
                flushprint("F");
            } else if(showOpen || IS_OPENED(field_value)) {
                flushprint("%c", '0' + MINES_VALUE(field_value));
                //  '0' + MINES_VALUE(field_value);
            } else {
                flushprint(".");
            }
        }
        flushprint("\n");
    }
}


//------------------------------------------------------------------------------
bool Field_FindIndicesToOpen(u8 x, u8 y)
{
    u8 index;
    index = FIELD_INDEX(y, x);

    //
    // Reset the indices that were opened.
    Field_OpenIndicesCount   = 1;     // Always open at least one
    flood_fill_indices_index = 0;     // Start from the beginning.
    Field_OpenIndices[0]     = index; // Actually if is already open it will return false...

    //
    // Check if the position is good to be opened.
    if(IS_OPENED(Field[index])) {
        return false;
    }
    if(IS_FLAGGED(Field[index])) {
        return false;
    }

    if(HAS_BOMB(Field[index])) {
        _Field_FindBombs();
    } else {
        _Field_FindOpenBlocks(x, y);
    }

    //
    // Set them as open...
    for(index = 0; index < Field_OpenIndicesCount; ++index) {
        SET_OPEN(Field[Field_OpenIndices[index]]);
    }

    return true;
}

//------------------------------------------------------------------------------
void Field_ToggleFlag(u8 x, u8 y)
{
    u8 index = FIELD_INDEX(y, x);
    if(IS_OPENED(Field[index])) {
        return;
    }

    TOGGLE_FLAG(Field[index]);
}
