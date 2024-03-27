// Header
#include "breaking_block.h"
// Game
#include "objects/field.h"


U8 dd;
typedef struct BreakingBlock_Tag {
    U8 x;
    U8 y;

    U8   dis;
    U8   animation_time;
    BOOL is_alive;
} BreakingBlock_t;


BreakingBlock_t BreakingBlocks[BREAKING_BLOCKS_MAX_COUNT];

U8 _BlocksToDestroyCount;
U8 _CurrentDestroyedBlocks;
U8 _CurrentAnimating;
U8 _IsBombOpening;
U8 _BreakingBlocksCount;


//------------------------------------------------------------------------------
void
_BreakingBlocks_ResetBlock(U8 index)
{
    U8 field_x;
    U8 field_y;
    U8 duration;

    if(_CurrentDestroyedBlocks < _BlocksToDestroyCount) {
        field_x = Field_OpenIndices[_CurrentDestroyedBlocks] % FieldCols;
        field_y = Field_OpenIndices[_CurrentDestroyedBlocks] / FieldCols;

        duration =
        // gprintxy(0, 10, "RB: %u", index);
        BreakingBlocks[index].x = field_x * TILE_SIZE_x2 + FIRST_PIXEL_X;
        BreakingBlocks[index].y = field_y * TILE_SIZE_x2 + FIRST_PIXEL_Y;

        BreakingBlocks[index].is_alive       = TRUE;
        BreakingBlocks[index].dis            = 0;
        BreakingBlocks[index].animation_time = Random_U8(
            BREAKING_BLOCK_ANIMATION_TIME_MIN,
            BREAKING_BLOCK_ANIMATION_TIME_MAX
        );
        ++_CurrentDestroyedBlocks;
        ++_CurrentAnimating;

        Bkg_UpdateTile(field_y, field_x);
    } else {
        BreakingBlocks[index].is_alive = FALSE;
    }
}

//------------------------------------------------------------------------------
void
_BreakingBlocks_MoveSprite(U8 index)
{
    U8 sprite_index;
    sprite_index = BREAKING_BLOCK_SPRITE_ID_FIRST * (index + 1);

    if(BreakingBlocks[index].is_alive) {
        ++BreakingBlocks[index].dis;
        #define dd BreakingBlocks[index].dis

        move_sprite(sprite_index + 0, BreakingBlocks[index].x             - dd, BreakingBlocks[index].y             - dd);
        move_sprite(sprite_index + 1, BreakingBlocks[index].x             - dd, BreakingBlocks[index].y + TILE_SIZE + dd);
        move_sprite(sprite_index + 2, BreakingBlocks[index].x + TILE_SIZE + dd, BreakingBlocks[index].y             - dd);
        move_sprite(sprite_index + 3, BreakingBlocks[index].x + TILE_SIZE + dd, BreakingBlocks[index].y + TILE_SIZE + dd);
    }
}


//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
BreakingBlocks_Init()
{
    U8 index;
    U8 sprite_index;

    for(index = 0; index < _BreakingBlocksCount; ++index) {
        sprite_index = BREAKING_BLOCK_SPRITE_ID_FIRST * (index + 1);
        set_sprite_tile(sprite_index + 0, BREAKING_BLOCK_TILE_NO_FIRST    );
        set_sprite_tile(sprite_index + 1, BREAKING_BLOCK_TILE_NO_FIRST + 1);
        set_sprite_tile(sprite_index + 2, BREAKING_BLOCK_TILE_NO_FIRST + 2);
        set_sprite_tile(sprite_index + 3, BREAKING_BLOCK_TILE_NO_FIRST + 3);
    }
}

//------------------------------------------------------------------------------
void
BreakingBlocks_Start(U8 count, BOOL is_bomb_opening)
{
    U8 index;
    for(index = 0; index < BREAKING_BLOCKS_MAX_COUNT; ++index) {
        BreakingBlocks[index].is_alive = FALSE;
    }

    _BlocksToDestroyCount   = count;
    _IsBombOpening          = is_bomb_opening;
    _CurrentDestroyedBlocks = 0;
    _CurrentAnimating       = 0;
    _BreakingBlocksCount    = is_bomb_opening ? BREAKING_BLOCKS_BOMB_COUNT : BREAKING_BLOCKS_OPEN_COUNT;
}


//------------------------------------------------------------------------------
BOOL
BreakingBlocks_HasFinished()
{
    #if _PRINT_INFO
        return TRUE;
    #else
        return (_CurrentAnimating == 0)
            && (_CurrentDestroyedBlocks >= _BlocksToDestroyCount);
    #endif
}

//------------------------------------------------------------------------------
void
BreakingBlocks_End()
{
    U8 index;
    U8 sprite_index;
    for(index = 0; index < _BreakingBlocksCount; ++index) {
        sprite_index = BREAKING_BLOCK_SPRITE_ID_FIRST * (index + 1);

        move_sprite(sprite_index + 0, 0, 0);
        move_sprite(sprite_index + 1, 0, 0);
        move_sprite(sprite_index + 2, 0, 0);
        move_sprite(sprite_index + 3, 0, 0);
    }
}

//------------------------------------------------------------------------------
void
BreakingBlocks_Update()
{
    U8 index;
    for(index = 0; index < _BreakingBlocksCount; ++index) {
        if(BreakingBlocks_HasFinished()) {
            return;
        }

        if(BreakingBlocks[index].is_alive) {
            --BreakingBlocks[index].animation_time;
            _BreakingBlocks_MoveSprite(index);

            if(BreakingBlocks[index].animation_time == 1) {
                BreakingBlocks[index].is_alive = FALSE;
                --_CurrentAnimating;
            }
        } else {
            _BreakingBlocks_ResetBlock(index);
        }
    }
}
