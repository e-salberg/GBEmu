#include "cpu.h"
#include <cpu_opcodes.h>

// 0x0X
void instruction_00(cpu_t *cpu, mmu_t *mmu) { /* NO-OP */ }
void instruction_01(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_BC, cpu, mmu); }
void instruction_02(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_BC, cpu, mmu); }
void instruction_03(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_BC, cpu); }
void instruction_04(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_B, cpu, mmu); }
void instruction_05(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_B, cpu, mmu); }
void instruction_06(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_B, cpu, mmu); }
void instruction_08(cpu_t *cpu, mmu_t *mmu) { ld_addr16_sp(cpu, mmu); }
void instruction_0A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_BC, cpu, mmu); }
void instruction_0B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_BC, cpu); }
void instruction_0C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_C, cpu, mmu); }
void instruction_0D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_C, cpu, mmu); }
void instruction_0E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_C, cpu, mmu); }

// 0x1X
void instruction_11(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_DE, cpu, mmu); }
void instruction_12(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_DE, cpu, mmu); }
void instruction_13(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_DE, cpu); }
void instruction_14(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_D, cpu, mmu); }
void instruction_15(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_D, cpu, mmu); }
void instruction_16(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_D, cpu, mmu); }
void instruction_1A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_DE, cpu, mmu); }
void instruction_1B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_DE, cpu); }
void instruction_1C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_E, cpu, mmu); }
void instruction_1D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_E, cpu, mmu); }
void instruction_1E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_E, cpu, mmu); }

// 0x2X
void instruction_21(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_HL, cpu, mmu); }
void instruction_22(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_HLI, cpu, mmu); }
void instruction_23(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_HL, cpu); }
void instruction_24(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_H, cpu, mmu); }
void instruction_25(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_H, cpu, mmu); }
void instruction_26(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_H, cpu, mmu); }
void instruction_2A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_HLI, cpu, mmu); }
void instruction_2B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_HL, cpu); }
void instruction_2C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_L, cpu, mmu); }
void instruction_2D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_L, cpu, mmu); }
void instruction_2E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_L, cpu, mmu); }

// 0x3X
void instruction_31(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_SP, cpu, mmu); }
void instruction_32(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_HLD, cpu, mmu); }
void instruction_33(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_SP, cpu); }
void instruction_34(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_HL, cpu, mmu); }
void instruction_35(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_HL, cpu, mmu); }
void instruction_36(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_HL, cpu, mmu); }
void instruction_3A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_HLD, cpu, mmu); }
void instruction_3B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_SP, cpu); }
void instruction_3C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_A, cpu, mmu); }
void instruction_3D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_A, cpu, mmu); }
void instruction_3E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_A, cpu, mmu); }

// 0x4X
void instruction_40(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_B, cpu, mmu); }
void instruction_41(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_C, cpu, mmu); }
void instruction_42(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_D, cpu, mmu); }
void instruction_43(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_E, cpu, mmu); }
void instruction_44(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_H, cpu, mmu); }
void instruction_45(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_L, cpu, mmu); }
void instruction_46(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_HL, cpu, mmu); }
void instruction_47(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_B, RT_A, cpu, mmu); }
void instruction_48(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_B, cpu, mmu); }
void instruction_49(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_C, cpu, mmu); }
void instruction_4A(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_D, cpu, mmu); }
void instruction_4B(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_E, cpu, mmu); }
void instruction_4C(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_H, cpu, mmu); }
void instruction_4D(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_L, cpu, mmu); }
void instruction_4E(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_HL, cpu, mmu); }
void instruction_4F(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_C, RT_A, cpu, mmu); }

// 0x5X
void instruction_50(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_B, cpu, mmu); }
void instruction_51(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_C, cpu, mmu); }
void instruction_52(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_D, cpu, mmu); }
void instruction_53(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_E, cpu, mmu); }
void instruction_54(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_H, cpu, mmu); }
void instruction_55(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_L, cpu, mmu); }
void instruction_56(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_HL, cpu, mmu); }
void instruction_57(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_D, RT_A, cpu, mmu); }
void instruction_58(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_B, cpu, mmu); }
void instruction_59(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_C, cpu, mmu); }
void instruction_5A(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_D, cpu, mmu); }
void instruction_5B(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_E, cpu, mmu); }
void instruction_5C(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_H, cpu, mmu); }
void instruction_5D(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_L, cpu, mmu); }
void instruction_5E(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_HL, cpu, mmu); }
void instruction_5F(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_E, RT_A, cpu, mmu); }

// 0x6X
void instruction_60(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_B, cpu, mmu); }
void instruction_61(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_C, cpu, mmu); }
void instruction_62(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_D, cpu, mmu); }
void instruction_63(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_E, cpu, mmu); }
void instruction_64(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_H, cpu, mmu); }
void instruction_65(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_L, cpu, mmu); }
void instruction_66(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_HL, cpu, mmu); }
void instruction_67(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_H, RT_A, cpu, mmu); }
void instruction_68(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_B, cpu, mmu); }
void instruction_69(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_C, cpu, mmu); }
void instruction_6A(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_D, cpu, mmu); }
void instruction_6B(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_E, cpu, mmu); }
void instruction_6C(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_H, cpu, mmu); }
void instruction_6D(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_L, cpu, mmu); }
void instruction_6E(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_HL, cpu, mmu); }
void instruction_6F(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_L, RT_A, cpu, mmu); }

// 0x7X
void instruction_70(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_B, cpu, mmu); }
void instruction_71(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_C, cpu, mmu); }
void instruction_72(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_D, cpu, mmu); }
void instruction_73(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_E, cpu, mmu); }
void instruction_74(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_H, cpu, mmu); }
void instruction_75(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_L, cpu, mmu); }
void instruction_76(cpu_t *cpu, mmu_t *mmu) { /* HALT */ }
void instruction_77(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_A, cpu, mmu); }
void instruction_78(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_B, cpu, mmu); }
void instruction_79(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_C, cpu, mmu); }
void instruction_7A(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_D, cpu, mmu); }
void instruction_7B(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_E, cpu, mmu); }
void instruction_7C(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_H, cpu, mmu); }
void instruction_7D(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_L, cpu, mmu); }
void instruction_7E(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_HL, cpu, mmu); }
void instruction_7F(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_A, cpu, mmu); }

opfunc_t optable[0x100] = {
    // 0x0X
    [0x00] = instruction_00,
    [0x01] = instruction_01,
    [0x02] = instruction_02,
    [0x03] = instruction_03,
    [0x04] = instruction_04,
    [0x05] = instruction_05,
    [0x06] = instruction_06,
    [0x08] = instruction_08,
    [0x0A] = instruction_0A,
    [0x0B] = instruction_0B,
    [0x0C] = instruction_0C,
    [0x0D] = instruction_0D,
    [0x0E] = instruction_0E,

    // 0x1X
    [0x11] = instruction_11,
    [0x12] = instruction_12,
    [0x13] = instruction_13,
    [0x14] = instruction_14,
    [0x15] = instruction_15,
    [0x16] = instruction_16,
    [0x1A] = instruction_1A,
    [0x1B] = instruction_1B,
    [0x1C] = instruction_1C,
    [0x1D] = instruction_1D,
    [0x1E] = instruction_1E,

    // 0x2X
    [0x21] = instruction_21,
    [0x22] = instruction_22,
    [0x23] = instruction_23,
    [0x24] = instruction_24,
    [0x25] = instruction_25,
    [0x26] = instruction_26,
    [0x2A] = instruction_2A,
    [0x2B] = instruction_2B,
    [0x2C] = instruction_2C,
    [0x2D] = instruction_2D,
    [0x2E] = instruction_2E,

    // 0x3X
    [0x31] = instruction_31,
    [0x32] = instruction_32,
    [0x33] = instruction_33,
    [0x34] = instruction_34,
    [0x35] = instruction_35,
    [0x36] = instruction_36,
    [0x3A] = instruction_3A,
    [0x3B] = instruction_3B,
    [0x3C] = instruction_3C,
    [0x3D] = instruction_3D,
    [0x3E] = instruction_3E,

    // 0x4X
    [0x40] = instruction_40,
    [0x41] = instruction_41,
    [0x42] = instruction_42,
    [0x43] = instruction_43,
    [0x44] = instruction_44,
    [0x45] = instruction_45,
    [0x46] = instruction_46,
    [0x47] = instruction_47,
    [0x48] = instruction_48,
    [0x49] = instruction_49,
    [0x4A] = instruction_4A,
    [0x4B] = instruction_4B,
    [0x4C] = instruction_4C,
    [0x4D] = instruction_4D,
    [0x4E] = instruction_4E,
    [0x4F] = instruction_4F,

    // 0x5X
    [0x50] = instruction_50,
    [0x51] = instruction_51,
    [0x52] = instruction_52,
    [0x53] = instruction_53,
    [0x54] = instruction_54,
    [0x55] = instruction_55,
    [0x56] = instruction_56,
    [0x57] = instruction_57,
    [0x58] = instruction_58,
    [0x59] = instruction_59,
    [0x5A] = instruction_5A,
    [0x5B] = instruction_5B,
    [0x5C] = instruction_5C,
    [0x5D] = instruction_5D,
    [0x5E] = instruction_5E,
    [0x5F] = instruction_5F,

    // 0x6X
    [0x60] = instruction_60,
    [0x61] = instruction_61,
    [0x62] = instruction_62,
    [0x63] = instruction_63,
    [0x64] = instruction_64,
    [0x65] = instruction_65,
    [0x66] = instruction_66,
    [0x67] = instruction_67,
    [0x68] = instruction_68,
    [0x69] = instruction_69,
    [0x6A] = instruction_6A,
    [0x6B] = instruction_6B,
    [0x6C] = instruction_6C,
    [0x6D] = instruction_6D,
    [0x6E] = instruction_6E,
    [0x6F] = instruction_6F,

    // 0x7X
    [0x70] = instruction_70,
    [0x71] = instruction_71,
    [0x72] = instruction_72,
    [0x73] = instruction_73,
    [0x74] = instruction_74,
    [0x75] = instruction_75,
    [0x76] = instruction_76,
    [0x77] = instruction_77,
    [0x78] = instruction_78,
    [0x79] = instruction_79,
    [0x7A] = instruction_7A,
    [0x7B] = instruction_7B,
    [0x7C] = instruction_7C,
    [0x7D] = instruction_7D,
    [0x7E] = instruction_7E,
    [0x7F] = instruction_7F,
};

char *inst_to_string[0x100] = {
    // 0x0X
    [0x00] = "NOP",
    [0x01] = "LD BC, n16",
    [0x02] = "LD [BC], A",
    [0x03] = "INC BC",
    [0x04] = "INC B",
    [0x05] = "DEC B",
    [0x06] = "LD B, n8",
    [0x07] = "",
    [0x08] = "LD [a16], SP",
    [0x09] = "",
    [0x0A] = "LD A, [BC]",
    [0x0B] = "DEC BC",
    [0x0C] = "INC C",
    [0x0D] = "DEC C",
    [0x0E] = "LD C, n8",
    [0x0F] = "",

    // 0x1X
    [0x10] = "",
    [0x11] = "LD DE, n16",
    [0x12] = "LD [DE], A",
    [0x13] = "INC DE",
    [0x14] = "INC D",
    [0x15] = "DEC D",
    [0x16] = "LD D, n8",
    [0x17] = "",
    [0x18] = "",
    [0x19] = "",
    [0x1A] = "LD A, [DE]",
    [0x1B] = "DEC DE",
    [0x1C] = "INC E",
    [0x1D] = "DEC E",
    [0x1E] = "LD E, n8",
    [0x1F] = "",

    // 0x2X
    [0x20] = "",
    [0x21] = "LD HL, n16",
    [0x22] = "LD [HL+], A",
    [0x23] = "INC HL",
    [0x24] = "INC H",
    [0x25] = "DEC H",
    [0x26] = "LD H, n8",
    [0x27] = "",
    [0x28] = "",
    [0x29] = "",
    [0x2A] = "LD A, [HLI]",
    [0x2B] = "DEC HL",
    [0x2C] = "INC L",
    [0x2D] = "DEC L",
    [0x2E] = "LD L, n8",
    [0x2F] = "",

    // 0x3X
    [0x30] = "",
    [0x31] = "LD SP, n16",
    [0x32] = "LD [HL-], A",
    [0x33] = "INC SP",
    [0x34] = "INC [HL]",
    [0x35] = "DEC [HL]",
    [0x36] = "LD [HL], n8",
    [0x37] = "",
    [0x38] = "",
    [0x39] = "",
    [0x3A] = "LD A, [HLD]",
    [0x3B] = "DEC SP",
    [0x3C] = "INC A",
    [0x3D] = "DEC A",
    [0x3E] = "LD A, n8",
    [0x3F] = "",

    // 0x4X
    [0x40] = "LD B, B",
    [0x41] = "LD B, C",
    [0x42] = "LD B, D",
    [0x43] = "LD B, E",
    [0x44] = "LD B, H",
    [0x45] = "LD B, L",
    [0x46] = "LD B, [HL]",
    [0x47] = "LD B, A",
    [0x48] = "LD C, B",
    [0x49] = "LD C, C",
    [0x4A] = "LD C, D",
    [0x4B] = "LD C, E",
    [0x4C] = "LD C, H",
    [0x4D] = "LD C, L",
    [0x4E] = "LD C, [HL]",
    [0x4F] = "LD C, A",

    // 0x5X
    [0x50] = "LD D, B",
    [0x51] = "LD D, C",
    [0x52] = "LD D, D",
    [0x53] = "LD D, E",
    [0x54] = "LD D, H",
    [0x55] = "LD D, L",
    [0x56] = "LD D, [HL]",
    [0x57] = "LD D, A",
    [0x58] = "LD E, B",
    [0x59] = "LD E, C",
    [0x5A] = "LD E, D",
    [0x5B] = "LD E, E",
    [0x5C] = "LD E, H",
    [0x5D] = "LD E, L",
    [0x5E] = "LD E, [HL]",
    [0x5F] = "LD E, A",

    // 0x6X
    [0x60] = "LD H, B",
    [0x61] = "LD H, C",
    [0x62] = "LD H, D",
    [0x63] = "LD H, E",
    [0x64] = "LD H, H",
    [0x65] = "LD H, L",
    [0x66] = "LD H, [HL]",
    [0x67] = "LD H, A",
    [0x68] = "LD L, B",
    [0x69] = "LD L, C",
    [0x6A] = "LD L, D",
    [0x6B] = "LD L, E",
    [0x6C] = "LD L, H",
    [0x6D] = "LD L, L",
    [0x6E] = "LD L, [HL]",
    [0x6F] = "LD L, A",

    // 0x7X
    [0x70] = "LD [HL], B",
    [0x71] = "LD [HL], C",
    [0x72] = "LD [HL], D",
    [0x73] = "LD [HL], E",
    [0x74] = "LD [HL], H",
    [0x75] = "LD [HL], L",
    [0x76] = "HALT",
    [0x77] = "LD [HL], A",
    [0x78] = "LD A, B",
    [0x79] = "LD A, C",
    [0x7A] = "LD A, D",
    [0x7B] = "LD A, E",
    [0x7C] = "LD A, H",
    [0x7D] = "LD A, L",
    [0x7E] = "LD A, [HL]",
    [0x7F] = "LD A, A",

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
