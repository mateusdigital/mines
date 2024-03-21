#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//------------------------------------------------------------------------------
#include "mdgb.h"
#include "globals.h"

//------------------------------------------------------------------------------
extern u8 curr_screen_type;
extern u8 curr_level;

void (*curr_screen_func)();

#endif // __GLOBALS_H__