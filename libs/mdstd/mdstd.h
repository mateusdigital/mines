// -----------------------------------------------------------------------------
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//
// Types
//

// -----------------------------------------------------------------------------
#define bool uint8_t
#define u8   uint8_t
#define u16  uint16_t
#define i8   int8_t
#define i16  int16_t

#define bool u8
#define false 0
#define true  (!(false))


//
// Random
//

// -----------------------------------------------------------------------------
u8 Rand_u8();
u8 Rand_u8_ex(u8 min, u8 max);

//
// Print
//

// -----------------------------------------------------------------------------
#define flushprint(s, ...) do { printf(s, __VA_ARGS__); fflush(stdout); } while(0);
