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
//  File      : mdstd.c                                                       //
//  Project   : mateus.digital - standardlib                                  //
//  Date      : 2024-03-21                                                    //
//  License   : See project's COPYING.TXT for full info.                      //
//  Author    : mateus.digital <hello@mateus.digital>                         //
//  Copyright : mateus.digital - 2024                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#ifndef __MDSTD_C__
#define __MDSTD_C__

//------------------------------------------------------------------------------
#include "mdstd.h"

//
// Random
//

// -----------------------------------------------------------------------------
u8 Rand_u8()
{
    return (u8)(rand() % 255);
}

// -----------------------------------------------------------------------------
u8 Rand_u8_ex(u8 min, u8 max)
{
    return min + (Rand_u8() % (max - min));
}

#endif // __MDSTD_C__