// Header
#include "cursor.h"


Cursor_t Cursor;

void
_Cursor_UpdateFrame()
{
    if(Cursor.blink_frame & CURSOR_BLINK_FRAMES_COUNT) {
        move_sprite(CURSOR_SPRITE_ID_FIRST + 0, Cursor.x,             Cursor.y            );
        move_sprite(CURSOR_SPRITE_ID_FIRST + 1, Cursor.x,             Cursor.y + TILE_SIZE);
        move_sprite(CURSOR_SPRITE_ID_FIRST + 2, Cursor.x + TILE_SIZE, Cursor.y            );
        move_sprite(CURSOR_SPRITE_ID_FIRST + 3, Cursor.x + TILE_SIZE, Cursor.y + TILE_SIZE);
    } else {
        move_sprite(CURSOR_SPRITE_ID_FIRST + 0, 0, 0);
        move_sprite(CURSOR_SPRITE_ID_FIRST + 1, 0, 0);
        move_sprite(CURSOR_SPRITE_ID_FIRST + 2, 0, 0);
        move_sprite(CURSOR_SPRITE_ID_FIRST + 3, 0, 0);
    }
}

void
Cursor_Init()
{
    Cursor.x           = FIRST_PIXEL_X;
    Cursor.y           = FIRST_PIXEL_Y;
    Cursor.blink_frame = 0;

    set_sprite_tile(CURSOR_SPRITE_ID_FIRST    , CURSOR_TILE_NO_FIRST    );
    set_sprite_tile(CURSOR_SPRITE_ID_FIRST + 1, CURSOR_TILE_NO_FIRST + 1);
    set_sprite_tile(CURSOR_SPRITE_ID_FIRST + 2, CURSOR_TILE_NO_FIRST + 2);
    set_sprite_tile(CURSOR_SPRITE_ID_FIRST + 3, CURSOR_TILE_NO_FIRST + 3);

    _Cursor_UpdateFrame();
}

void
Cursor_Update()
{
    //
    // Movement...
    if(JOY_CLICK(J_LEFT)) {
        Cursor.x -= TILE_SIZE_x2;
    } else if(JOY_CLICK(J_RIGHT)) {
        Cursor.x += TILE_SIZE_x2;
    } else if(JOY_CLICK(J_UP)) {
        Cursor.y -= TILE_SIZE_x2;
    } else if(JOY_CLICK(J_DOWN)) {
        Cursor.y += TILE_SIZE_x2;
    }

    //
    // Update Sprite.
    #if _PRINT_INFO
        gprintxy(0, 11, "--%u %u", Cursor.y, Cursor.x);
        gprintxy(0, 10, "%u %u",  (Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2, (Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2);
    #else
        ++Cursor.blink_frame;
        _Cursor_UpdateFrame();
    #endif // _PRINT_INFO
}
