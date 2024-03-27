#include <stdio.h>

#ifdef MDGB
#elif MDDOS
#elif MDSTD
#include "mdstd/mdstd.h"
#include "core_defs.h"
#endif


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
extern u8 Field[FIELD_ARRAY_SIZE];

extern u8 FieldCols;
extern u8 FieldRows;
extern u8 FieldMinesCount;

extern u8 Field_OpenIndices[FIELD_ARRAY_SIZE];
extern u8 Field_OpenIndicesCount;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
void Field_Init(u8 rows, u8 cols, u8 minesCount);
void Field_PrintDebug(bool showOpen);
void Field_ToggleFlag(u8 x, u8 y);
bool Field_FindIndicesToOpen(u8 x, u8 y);


