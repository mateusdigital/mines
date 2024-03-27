
#include "sound_test.c"


U8
add_high(U8 value, I8 v)
{
    return ((((value & 0xF0) >> 4) + v) << 4) | (value & 0x0F);
}


void
Print_Bin(U8 y, int value, U8 bin_x)
{
    U8 i;
    U8 x;
    U8 b;

    ++y;
    gprintxy(0, y, "V: %u ", value);

    ++y;
    x = 0;
    for(i = 0; i < 8; ++i, ++x) {
        b = (value >> i & 1);
        if(i == 4) {
            ++x;
        }

        gprintxy(8 -x, y, "%x", (U8)b);
    }
    ++y;
    gprintxy(0, y, "         ");
    gprintxy(bin_x, y, "*");
}

void
SoundTest_Update()
{
    U8 reg_selected;
    U8 index;
    U8 y;
    U8 is_selected;

    BOOL bin_edit;
    BOOL bin_y;
    BOOL bin_x;

    #define CONTROL_REGS_COUNT 3
    #define SOUND_REGS_COUNT   5

    U16 control_addrs[CONTROL_REGS_COUNT] = {
        NR50_REG_ADDR,
        NR51_REG_ADDR,
        NR52_REG_ADDR,
    };

    U16 sound_addrs[SOUND_REGS_COUNT] = {
        NR10_REG_ADDR,
        NR11_REG_ADDR,
        NR12_REG_ADDR,
        NR13_REG_ADDR,
        NR14_REG_ADDR
    };

    Random_Init(2); // Seed in RELEASE mode is ignored...
    Input_Reset();

    index        = 0;
    reg_selected = 0;
    bin_edit     = FALSE;
    bin_x       = 0;
    #define R(_addr_) (*(__REG)(_addr_))

    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them.
                     // One bit for the L one bit for the R of all four channels

    #define Print_Control(_y_, _name_, _addr_) \
        gprintxy(0, _y_, " R%u: %x ", (U16)_name_, (U8)R(_addr_))

    #define Print_Sound(_y_, _name_, _addr_, _val_, _sel_) {           \
        if(_sel_) {                                             \
            gprintxy(0, _y_, "*");                               \
        } else {                                                \
            gprintxy(0, _y_, " ");                               \
        }                                                       \
        gprintxy(1, _y_, "R%u: %x - %x ", (U16)_name_, (U8)R(_addr_), (U8)_val_) ; \
    }

    while(1) {
        Input_BeginFrame();
        y = 0;

        // Print Registers;
        for(index = 0; index < 3; ++index) {
            ++y;
            Print_Control(y, 50 + index, control_addrs[index]);
        }

        ++y;

        for(index = 0; index < 5; ++index) {
            ++y;
            is_selected = (reg_selected == index);
            Print_Sound(y, 10 + index, sound_addrs[index], sound_values[index], is_selected);
        }


        //
        // Select Register
        if(JOY_CLICK(J_UP)) {
            if(reg_selected == 0) {
                reg_selected = (SOUND_REGS_COUNT -1);
            } else {
                --reg_selected;
            }
        } else if(JOY_CLICK(J_DOWN)) {
            ++reg_selected;
            if(reg_selected >= SOUND_REGS_COUNT) {
                reg_selected = 0;
            }
        }

        if(JOY_CLICK(J_SELECT)) {
            if(bin_edit == FALSE) {
                bin_edit = TRUE;
            } else {
                bin_edit = FALSE;
            }
        }

        //
        // Select Values
        if(!bin_edit) {
            if(JOY_PRESS(J_LEFT)) {
                if(JOY_PRESS(J_B)) {
                    sound_values[reg_selected] = add_high(sound_values[reg_selected], -1);
                } else {
                    sound_values[reg_selected] -= 1;
                }
            } else if(JOY_PRESS(J_RIGHT)) {
                if(JOY_PRESS(J_B)) {
                    sound_values[reg_selected] = add_high(sound_values[reg_selected], +1);
                } else {
                    sound_values[reg_selected] += 1;
                }
            }
        }

        ++y;

        Print_Bin(y, sound_values[reg_selected], bin_x);
        if(bin_edit){
            if(JOY_PRESS(J_LEFT)) {
                --bin_x;
                if(bin_x == 4) {
                    bin_x = 3;
                }
            } else if(JOY_PRESS(J_RIGHT)) {
                ++bin_x;

                if(bin_x == 4) {
                    bin_x = 5;
                }
            } else if(JOY_CLICK(J_B)) {
                if(bin_x > 4) {
                    sound_values[reg_selected] ^= 1 << (7 - (bin_x - 1));
                } else {
                    sound_values[reg_selected] ^= 1 << (7 - bin_x);
                }
            }
        }




        //
        // Play...
        if(JOY_CLICK(J_A)) {
            NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
            NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
            NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them.
                     // One bit for the L one bit for the R of all four channels
            for(index = 0; index < SOUND_REGS_COUNT; ++index) {
                R(sound_addrs[index]) = sound_values[index];
            }
        }
        // Screen_Update();


            // chanel 1 register 2: Volume Envelope (Makes the volume get louder or quieter each "tick")
            // On Channels 1 2 and 4
            // 7-4	(Initial) Channel Volume
            // 3	Volume sweep direction (0: down; 1: up)
            // 2-0	Length of each step in sweep (if 0, sweeping is off)
            // NOTE: each step is n/64 seconds long, where n is 1-7
            // 0111 0011 is 0x73, volume 7, sweep down, step length 3

            // chanel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
            // for Channels 1 2 and 3
            // 7-0	8 Least Significant bits of frequency (3 Most Significant Bits are set in register 4)

            // chanel 1 register 4: Playback and frequency MSbs
            // Channels 1 2 3 and 4
            // 7	Initialize (trigger channel start, AKA channel INIT) (Write only)
            // 6	Consecutive select/length counter enable (Read/Write). When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
            // 5-3	Unused
            // 2-0	3 Most Significant bits of frequency
            // 1100 0011 is 0xC3, initialize, no consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300

        Input_EndFrame();
    }
}
