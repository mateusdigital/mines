// Header
#include "objects/field.h"

//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
// Public
U8 Field[FIELD_ARRAY_SIZE] = {0};

U8 FieldCols;
U8 FieldRows;
U8 MinesCount;


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
        Field[index] |= MASK_OPEN;
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
