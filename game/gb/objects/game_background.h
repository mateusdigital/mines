//~---------------------------------------------------------------------------//
//                               *       +                                    //
//                         '                  |                               //
//                     ()    .-.,="``"=.    - o -                             //
//                           '=/_       \     |                               //
//                        *   |  '=._    |                                    //
//                             \     `=./`,        '                          //
//                          .   '=.__.=' `='      *                           //
//                 +                         +                                //
//                      O      *        '       .                             //
//                                                                            //
//  File      : game_background.h                                             //
//  Project   : mines                                                         //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//


#ifndef __GAME_BACKGROUND_H__
#define __GAME_BACKGROUND_H__

//------------------------------------------------------------------------------
#include "mdgb/mdgb.h"
#include "globals.h"


//------------------------------------------------------------------------------
extern i8 BackgroundOffsetX;
extern i8 BackgroundOffsetY;

//------------------------------------------------------------------------------
void game_background_init();
void game_background_update();

void game_background_set_offset(i8 offset_x, i8 offset_y);
void game_background_open_tile_xy(u8 x, u8 y);

#endif // __GAME_BACKGROUND_H__