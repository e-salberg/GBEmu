#include <cpu_opcodes.h>

// 0x0X
void instruction_00(cpu_t *cpu, mmu_t *mmu) { /* NO-OP */ }
void instruction_03(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_BC, cpu); }
void instruction_04(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_B, cpu, mmu); }
void instruction_05(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_B, cpu, mmu); }
void instruction_0B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_BC, cpu); }
void instruction_0C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_C, cpu, mmu); }
void instruction_0D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_C, cpu, mmu); }

// 0x1X
void instruction_13(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_DE, cpu); }
void instruction_14(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_D, cpu, mmu); }
void instruction_15(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_D, cpu, mmu); }
void instruction_1B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_DE, cpu); }
void instruction_1C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_E, cpu, mmu); }
void instruction_1D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_E, cpu, mmu); }

// 0x2X
void instruction_23(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_HL, cpu); }
void instruction_24(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_H, cpu, mmu); }
void instruction_25(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_H, cpu, mmu); }
void instruction_2B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_HL, cpu); }
void instruction_2C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_L, cpu, mmu); }
void instruction_2D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_L, cpu, mmu); }

// 0x3X
void instruction_33(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_SP, cpu); }
void instruction_34(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_HL, cpu, mmu); }
void instruction_35(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_HL, cpu, mmu); }
void instruction_3B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_SP, cpu); }
void instruction_3C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_A, cpu, mmu); }
void instruction_3D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_A, cpu, mmu); }

opfunc_t optable[0x100] = {
    // 0x0X
    [0x00] = instruction_00,
    [0x03] = instruction_03,
    [0x04] = instruction_04,
    [0x05] = instruction_05,
    [0x0B] = instruction_0B,
    [0x0C] = instruction_0C,
    [0x0D] = instruction_0D,

    // 0x1X
    [0x13] = instruction_13,
    [0x14] = instruction_14,
    [0x15] = instruction_15,
    [0x1B] = instruction_1B,
    [0x1C] = instruction_1C,
    [0x1D] = instruction_1D,

    // 0x2X
    [0x23] = instruction_23,
    [0x24] = instruction_24,
    [0x25] = instruction_25,
    [0x2B] = instruction_2B,
    [0x2C] = instruction_2C,
    [0x2D] = instruction_2D,

    // 0x3X
    [0x33] = instruction_33,
    [0x34] = instruction_34,
    [0x35] = instruction_35,
    [0x3B] = instruction_3B,
    [0x3C] = instruction_3C,
    [0x3D] = instruction_3D,
};

char *inst_to_string[0x100] = {
    // 0x0X
    [0x00] = "NOP",
    [0x03] = "INC BC",
    [0x04] = "INC B",
    [0x05] = "DEC B",
    [0x06] = "",
    [0x07] = "",
    [0x08] = "",
    [0x09] = "",
    [0x0A] = "",
    [0x0B] = "DEC BC",
    [0x0C] = "INC C",
    [0x0D] = "DEC C",
    [0x0E] = "",
    [0x0F] = "",

    // 0x1X
    [0x10] = "",
    [0x11] = "",
    [0x12] = "",
    [0x13] = "INC DE",
    [0x14] = "INC D",
    [0x15] = "DEC D",
    [0x16] = "",
    [0x17] = "",
    [0x18] = "",
    [0x19] = "",
    [0x1A] = "",
    [0x1B] = "DEC DE",
    [0x1C] = "INC E",
    [0x1D] = "DEC E",
    [0x1E] = "",
    [0x1F] = "",

    // 0x2X
    [0x20] = "",
    [0x21] = "",
    [0x22] = "",
    [0x23] = "INC HL",
    [0x24] = "INC H",
    [0x25] = "DEC H",
    [0x26] = "",
    [0x27] = "",
    [0x28] = "",
    [0x29] = "",
    [0x2A] = "",
    [0x2B] = "DEC HL",
    [0x2C] = "INC L",
    [0x2D] = "DEC L",
    [0x2E] = "",
    [0x2F] = "",

    // 0x3X
    [0x30] = "",
    [0x31] = "",
    [0x32] = "",
    [0x33] = "INC SP",
    [0x34] = "INC [HL]",
    [0x35] = "DEC [HL]",
    [0x36] = "",
    [0x37] = "",
    [0x38] = "",
    [0x39] = "",
    [0x3A] = "",
    [0x3B] = "DEC SP",
    [0x3C] = "INC A",
    [0x3D] = "DEC A",
    [0x3E] = "",
    [0x3F] = "",

    // 0x4X
    [0x40] = "",
    [0x41] = "",
    [0x42] = "",
    [0x43] = "",
    [0x44] = "",
    [0x45] = "",
    [0x46] = "",
    [0x47] = "",
    [0x48] = "",
    [0x49] = "",
    [0x4A] = "",
    [0x4B] = "",
    [0x4C] = "",
    [0x4D] = "",
    [0x4E] = "",
    [0x4F] = "",

    // 0x5X
    [0x50] = "",
    [0x51] = "",
    [0x52] = "",
    [0x53] = "",
    [0x54] = "",
    [0x55] = "",
    [0x56] = "",
    [0x57] = "",
    [0x58] = "",
    [0x59] = "",
    [0x5A] = "",
    [0x5B] = "",
    [0x5C] = "",
    [0x5D] = "",
    [0x5E] = "",
    [0x5F] = "",

    // 0x6X
    [0x60] = "",
    [0x61] = "",
    [0x62] = "",
    [0x63] = "",
    [0x64] = "",
    [0x65] = "",
    [0x66] = "",
    [0x67] = "",
    [0x68] = "",
    [0x69] = "",
    [0x6A] = "",
    [0x6B] = "",
    [0x6C] = "",
    [0x6D] = "",
    [0x6E] = "",
    [0x6F] = "",

    // 0x7X
    [0x70] = "",
    [0x71] = "",
    [0x72] = "",
    [0x73] = "",
    [0x74] = "",
    [0x75] = "",
    [0x76] = "",
    [0x77] = "",
    [0x78] = "",
    [0x79] = "",
    [0x7A] = "",
    [0x7B] = "",
    [0x7C] = "",
    [0x7D] = "",
    [0x7E] = "",
    [0x7F] = "",

    // 0x8X
    [0x80] = "",
    [0x81] = "",
    [0x82] = "",
    [0x83] = "",
    [0x84] = "",
    [0x85] = "",
    [0x86] = "",
    [0x87] = "",
    [0x88] = "",
    [0x89] = "",
    [0x8A] = "",
    [0x8B] = "",
    [0x8C] = "",
    [0x8D] = "",
    [0x8E] = "",
    [0x8F] = "",

    // 0x9X
    [0x90] = "",
    [0x91] = "",
    [0x92] = "",
    [0x93] = "",
    [0x94] = "",
    [0x95] = "",
    [0x96] = "",
    [0x97] = "",
    [0x98] = "",
    [0x99] = "",
    [0x9A] = "",
    [0x9B] = "",
    [0x9C] = "",
    [0x9D] = "",
    [0x9E] = "",
    [0x9F] = "",

    // 0xAX
    [0xA0] = "",
    [0xA1] = "",
    [0xA2] = "",
    [0xA3] = "",
    [0xA4] = "",
    [0xA5] = "",
    [0xA6] = "",
    [0xA7] = "",
    [0xA8] = "",
    [0xA9] = "",
    [0xAA] = "",
    [0xAB] = "",
    [0xAC] = "",
    [0xAD] = "",
    [0xAE] = "",
    [0xAF] = "",

    // 0xBX
    [0xB0] = "",
    [0xB1] = "",
    [0xB2] = "",
    [0xB3] = "",
    [0xB4] = "",
    [0xB5] = "",
    [0xB6] = "",
    [0xB7] = "",
    [0xB8] = "",
    [0xB9] = "",
    [0xBA] = "",
    [0xBB] = "",
    [0xBC] = "",
    [0xBD] = "",
    [0xBE] = "",
    [0xBF] = "",

    // 0xCX
    [0xC0] = "",
    [0xC1] = "",
    [0xC2] = "",
    [0xC3] = "",
    [0xC4] = "",
    [0xC5] = "",
    [0xC6] = "",
    [0xC7] = "",
    [0xC8] = "",
    [0xC9] = "",
    [0xCA] = "",
    [0xCB] = "",
    [0xCC] = "",
    [0xCD] = "",
    [0xCE] = "",
    [0xCF] = "",

    // 0xDX
    [0xD0] = "",
    [0xD1] = "",
    [0xD2] = "",
    [0xD4] = "",
    [0xD5] = "",
    [0xD6] = "",
    [0xD7] = "",
    [0xD8] = "",
    [0xD9] = "",
    [0xDA] = "",
    [0xDC] = "",
    [0xDE] = "",
    [0xDF] = "",

    // 0xEX
    [0xE0] = "",
    [0xE1] = "",
    [0xE2] = "",
    [0xE5] = "",
    [0xE6] = "",
    [0xE7] = "",
    [0xE8] = "",
    [0xE9] = "",
    [0xEA] = "",
    [0xEE] = "",
    [0xEF] = "",

    // 0xFX
    [0xF0] = "",
    [0xF1] = "",
    [0xF2] = "",
    [0xF3] = "",
    [0xF5] = "",
    [0xF6] = "",
    [0xF7] = "",
    [0xF8] = "",
    [0xF9] = "",
    [0xFA] = "",
    [0xFB] = "",
    [0xFE] = "",
    [0xFF] = "",
};

char *get_instruction_string(uint8_t opcode) { return inst_to_string[opcode]; }

opfunc_t get_instruction(uint8_t opcode) { return optable[opcode]; }
