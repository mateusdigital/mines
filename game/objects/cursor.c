// Header
#include "cursor.h"


Cursor_t Cursor;


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

    Cursor_Show();
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
    ++Cursor.blink_frame;
    if(Cursor.blink_frame & CURSOR_BLINK_FRAMES_COUNT) {
        Cursor_Show();
    } else {
        Cursor_Hide();
    }
}


void
Cursor_Show()
{
    move_sprite(CURSOR_SPRITE_ID_FIRST + 0, Cursor.x,             Cursor.y            );
    move_sprite(CURSOR_SPRITE_ID_FIRST + 1, Cursor.x,             Cursor.y + TILE_SIZE);
    move_sprite(CURSOR_SPRITE_ID_FIRST + 2, Cursor.x + TILE_SIZE, Cursor.y            );
    move_sprite(CURSOR_SPRITE_ID_FIRST + 3, Cursor.x + TILE_SIZE, Cursor.y + TILE_SIZE);
}

void
Cursor_Hide()
{
    move_sprite(CURSOR_SPRITE_ID_FIRST + 0, 0, 0);
    move_sprite(CURSOR_SPRITE_ID_FIRST + 1, 0, 0);
    move_sprite(CURSOR_SPRITE_ID_FIRST + 2, 0, 0);
    move_sprite(CURSOR_SPRITE_ID_FIRST + 3, 0, 0);
}
