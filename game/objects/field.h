#ifndef __FIELD_H__
#define __FIELD_H__

// Game
#include "game_defs.h"


//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//
// 0000 0000
// |||| Number of mines
// |||| 0 - 15
// ||||
// ||||_ 1 - is open.
// |||__ 1 - is flag.
// ||___ 1 - has bomb.
// |____ 1 - has being used on the flood fill opening.
#define MASK_OPEN       (0x10)
#define MASK_FLAG       (0x20)
#define MASK_BOMB       (0x40)
#define MASK_FLOOD_FILL (0x80)
#define MASK_VALUE      (0x0F)


#define HAS_BOMB(_byte_)    (((_byte_) & MASK_BOMB)  != 0)
#define IS_OPENED(_byte_)   (((_byte_) & MASK_OPEN)  != 0)
#define IS_FLAGGED(_byte_)  (((_byte_) & MASK_FLAG)  != 0)
#define MINES_VALUE(_byte_) (((_byte_) & MASK_VALUE)     )


#define SET_OPEN(_byte_)    ((_byte_) |= MASK_OPEN)
#define TOGGLE_FLAG(_byte_) ((_byte_) ^= MASK_FLAG)


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
extern U8 Field[FIELD_ARRAY_SIZE];

extern U8 FieldCols;
extern U8 FieldRows;
extern U8 MinesCount;

extern U8 Field_OpenIndices[FIELD_ARRAY_SIZE];
extern U8 Field_OpenIndicesCount;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
void Field_Init();

I16 Field_ToOpenX;
I16 Field_ToOpenY;

BOOL Field_FindIndicesToOpen();
void Field_ToggleFlag(I8 y, I8 x);


#endif // __FIELD_H__
