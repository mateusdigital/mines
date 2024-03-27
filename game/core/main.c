//
#include "mines.h"


int main()
{
    srand(1234);
    Field_Init(10, 10, 3);
    Field_PrintDebug(true);

    Field_ToggleFlag(0, 0);
    Field_PrintDebug(true);

    Field_ToggleFlag(0, 0);
    Field_PrintDebug(true);

    bool opened = Field_FindIndicesToOpen(0, 0);
    flushprint("open: %d\n", opened);

    Field_PrintDebug(false);
    
}