#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

// Game
#include "game_defs.h"

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
#define TILE_ID_FLAG  10
#define TILE_ID_OPEN   1
#define TILE_ID_CLOSE  0
#define TILE_ID_BOMB  12

#define BIG_TILE_ID(_id_) (_id_ * 4)


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
extern U8 BackgroundTiles[BACKGROUND_TILES_COUNT];


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
void Bkg_Init();
void Bkg_Refresh();

void Bkg_UpdateShakeOffset();
void Bkg_ResetShakeOffset ();

void Bkg_UpdateTile(U8 y, U8 x);
#endif // __BACKGROUND_H__
