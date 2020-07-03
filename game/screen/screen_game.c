// Header
#include "screen_game.h"
// Game
#include "game_defs.h"
#include "objects/field.h"
#include "objects/background.h"


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
typedef struct Cursor_Tag {
    U8 x;
    U8 y;

    U8 blink_frame;
} Cursor_t;

Cursor_t Cursor;
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

    #if _PRINT_INFO
        gprintxy(0, 10, "%u %u",  (Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2, (Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2);
    #else
        ++Cursor.blink_frame;
        if(Cursor.blink_frame & 0x8) {
            move_sprite(0, Cursor.x,             Cursor.y            );
            move_sprite(1, Cursor.x,             Cursor.y + TILE_SIZE);
            move_sprite(2, Cursor.x + TILE_SIZE, Cursor.y            );
            move_sprite(3, Cursor.x + TILE_SIZE, Cursor.y + TILE_SIZE);
        } else {
            move_sprite(0, 0, 0);
            move_sprite(1, 0, 0);
            move_sprite(2, 0, 0);
            move_sprite(3, 0, 0);
        }
    #endif // _PRINT_INFO

    //
    // Action.
    if(JOY_CLICK(J_A)) {
        Field_Open(
            (Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2,
            (Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2
        );
        Bkg_Refresh();
    } else if(JOY_CLICK(J_B)) {
        Field_ToggleFlag(
            (Cursor.y - FIRST_PIXEL_Y) / TILE_SIZE_x2,
            (Cursor.x - FIRST_PIXEL_X) / TILE_SIZE_x2
        );
        Bkg_Refresh();
    }
}




//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
Game_Init()
{
    VBK_REG = 1;
    HIDE_SPRITES;
    HIDE_BKG;

    FieldRows  = FIELD_MAX_ROWS;
    FieldCols  = FIELD_MAX_COLS;
    MinesCount = 3;

    Cursor.x           = FIRST_PIXEL_X;
    Cursor.y           = FIRST_PIXEL_Y;
    Cursor.blink_frame = 0;

    set_sprite_data(0, 128, TILES_OBJECTS);
    set_sprite_tile(0, 64    );
    set_sprite_tile(1, 64 + 1);
    set_sprite_tile(2, 64 + 2);
    set_sprite_tile(3, 64 + 3);
    Random_Init(DIV_REG);

    Field_Init();
    Bkg_Init  ();


    SHOW_BKG;
    SHOW_SPRITES;
    VBK_REG = 0;
}

//------------------------------------------------------------------------------
void
Game_Update()
{
    U8 _delay;
    U8 a;

    Input_Reset();
    _delay = 1;

    a = 5;
    while(1) {
        Input_BeginFrame();
        Cursor_Update();

        Input_EndFrame();

        //
        // Refresh
        Delay(_delay);
        wait_vbl_done();
    }
}

//------------------------------------------------------------------------------
void
Game_Quit()
{
    // Empty...
}
