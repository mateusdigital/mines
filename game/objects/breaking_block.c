// Header
#include "breaking_block.h"

BreakingBlock_t BreakingBlock;
U8 dd;
void
BreakingBlock_Init()
{
    set_sprite_tile(BREAKING_BLOCK_SPRITE_ID_FIRST    , BREAKING_BLOCK_TILE_NO_FIRST    );
    set_sprite_tile(BREAKING_BLOCK_SPRITE_ID_FIRST + 1, BREAKING_BLOCK_TILE_NO_FIRST + 1);
    set_sprite_tile(BREAKING_BLOCK_SPRITE_ID_FIRST + 2, BREAKING_BLOCK_TILE_NO_FIRST + 2);
    set_sprite_tile(BREAKING_BLOCK_SPRITE_ID_FIRST + 3, BREAKING_BLOCK_TILE_NO_FIRST + 3);
}

void
BreakingBlock_Reset()
{
    BreakingBlock.x              = 0;
    BreakingBlock.y              = 0;
    BreakingBlock.blink_frame    = 0;
    BreakingBlock.animation_time = BREAKING_BLOCK_ANIMATION_TIME;
}

void
BreakingBlock_SetTilePos(U8 y, U8 x)
{
    BreakingBlock.x = x * TILE_SIZE_x2 + FIRST_PIXEL_X;
    BreakingBlock.y = y * TILE_SIZE_x2 + FIRST_PIXEL_Y;
    dd = 0;
}

void
BreakingBlock_Update()
{
    --BreakingBlock.animation_time;
    dd++;

    move_sprite(BREAKING_BLOCK_SPRITE_ID_FIRST + 0, BreakingBlock.x             - dd, BreakingBlock.y             - dd);
    move_sprite(BREAKING_BLOCK_SPRITE_ID_FIRST + 1, BreakingBlock.x             - dd, BreakingBlock.y + TILE_SIZE + dd);
    move_sprite(BREAKING_BLOCK_SPRITE_ID_FIRST + 2, BreakingBlock.x + TILE_SIZE + dd, BreakingBlock.y             - dd);
    move_sprite(BREAKING_BLOCK_SPRITE_ID_FIRST + 3, BreakingBlock.x + TILE_SIZE + dd, BreakingBlock.y + TILE_SIZE + dd);
}
