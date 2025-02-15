#include <instructions.h>

instruction instructions[0x100] = {
    // 0x0X
    [0x00] = { IN_NOP },

    // 0x4X
    [0x40] = { IN_LD, AM_R8_R8, RT_B, RT_B },
    [0x41] = { IN_LD, AM_R8_R8, RT_B, RT_C },
    [0x42] = { IN_LD, AM_R8_R8, RT_B, RT_D },
    [0x43] = { IN_LD, AM_R8_R8, RT_B, RT_E },
    [0x44] = { IN_LD, AM_R8_R8, RT_B, RT_H },
    [0x45] = { IN_LD, AM_R8_R8, RT_B, RT_L },
    
    [0x47] = { IN_LD, AM_R8_R8, RT_B, RT_A },
    [0x48] = { IN_LD, AM_R8_R8, RT_C, RT_B },
    [0x49] = { IN_LD, AM_R8_R8, RT_C, RT_C },
    [0x4A] = { IN_LD, AM_R8_R8, RT_C, RT_D },
    [0x4B] = { IN_LD, AM_R8_R8, RT_C, RT_E },
    [0x4C] = { IN_LD, AM_R8_R8, RT_C, RT_H },
    [0x4D] = { IN_LD, AM_R8_R8, RT_C, RT_L },

    [0x4F] = { IN_LD, AM_R8_R8, RT_C, RT_A },

    // 0x5X
    [0x50] = { IN_LD, AM_R8_R8, RT_D, RT_B },
    [0x51] = { IN_LD, AM_R8_R8, RT_D, RT_C },
    [0x52] = { IN_LD, AM_R8_R8, RT_D, RT_D },
    [0x53] = { IN_LD, AM_R8_R8, RT_D, RT_E },
    [0x54] = { IN_LD, AM_R8_R8, RT_D, RT_H },
    [0x55] = { IN_LD, AM_R8_R8, RT_D, RT_L },
    
    [0x57] = { IN_LD, AM_R8_R8, RT_D, RT_A },
    [0x58] = { IN_LD, AM_R8_R8, RT_E, RT_B },
    [0x59] = { IN_LD, AM_R8_R8, RT_E, RT_C },
    [0x5A] = { IN_LD, AM_R8_R8, RT_E, RT_D },
    [0x5B] = { IN_LD, AM_R8_R8, RT_E, RT_E },
    [0x5C] = { IN_LD, AM_R8_R8, RT_E, RT_H },
    [0x5D] = { IN_LD, AM_R8_R8, RT_E, RT_L },

    [0x5F] = { IN_LD, AM_R8_R8, RT_E, RT_A },

    // 0x6X
    [0x60] = { IN_LD, AM_R8_R8, RT_H, RT_B },
    [0x61] = { IN_LD, AM_R8_R8, RT_H, RT_C },
    [0x62] = { IN_LD, AM_R8_R8, RT_H, RT_D },
    [0x63] = { IN_LD, AM_R8_R8, RT_H, RT_E },
    [0x64] = { IN_LD, AM_R8_R8, RT_H, RT_H },
    [0x65] = { IN_LD, AM_R8_R8, RT_H, RT_L },
    
    [0x67] = { IN_LD, AM_R8_R8, RT_H, RT_A },
    [0x68] = { IN_LD, AM_R8_R8, RT_L, RT_B },
    [0x69] = { IN_LD, AM_R8_R8, RT_L, RT_C },
    [0x6A] = { IN_LD, AM_R8_R8, RT_L, RT_D },
    [0x6B] = { IN_LD, AM_R8_R8, RT_L, RT_E },
    [0x6C] = { IN_LD, AM_R8_R8, RT_L, RT_H },
    [0x6D] = { IN_LD, AM_R8_R8, RT_L, RT_L },

    [0x6F] = { IN_LD, AM_R8_R8, RT_L, RT_A },


    // 0xCX
    [0xC3] = { IN_JP, AM_IMM16 }

};

char* instruction_lookup[] = {
    [IN_NONE] = "NONE",
    [IN_NOP] = "NOP",
    [IN_LD] = "LD",
    [IN_JP] = "JP"
};


instruction *get_instruction_by_opcode(uint8_t opcode)
{
    return &instructions[opcode];
}

char *get_instruction_name(instruction_type type)
{
    return instruction_lookup[type];
}