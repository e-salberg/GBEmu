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
void instruction_07(cpu_t *cpu, mmu_t *mmu) { rlca(cpu); }
void instruction_08(cpu_t *cpu, mmu_t *mmu) { ld_addr16_sp(cpu, mmu); }
void instruction_09(cpu_t *cpu, mmu_t *mmu) { add_hl_r16(RT_BC, cpu, mmu); }
void instruction_0A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_BC, cpu, mmu); }
void instruction_0B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_BC, cpu); }
void instruction_0C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_C, cpu, mmu); }
void instruction_0D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_C, cpu, mmu); }
void instruction_0E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_C, cpu, mmu); }
void instruction_0F(cpu_t *cpu, mmu_t *mmu) { rrca(cpu); }

// 0x1X
void instruction_10(cpu_t *cpu, mmu_t *mmu) { stop(); }
void instruction_11(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_DE, cpu, mmu); }
void instruction_12(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_DE, cpu, mmu); }
void instruction_13(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_DE, cpu); }
void instruction_14(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_D, cpu, mmu); }
void instruction_15(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_D, cpu, mmu); }
void instruction_16(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_D, cpu, mmu); }
void instruction_17(cpu_t *cpu, mmu_t *mmu) { rla(cpu); }
void instruction_18(cpu_t *cpu, mmu_t *mmu) { jr_e8(CC_NONE, cpu, mmu); }
void instruction_19(cpu_t *cpu, mmu_t *mmu) { add_hl_r16(RT_DE, cpu, mmu); }
void instruction_1A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_DE, cpu, mmu); }
void instruction_1B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_DE, cpu); }
void instruction_1C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_E, cpu, mmu); }
void instruction_1D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_E, cpu, mmu); }
void instruction_1E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_E, cpu, mmu); }
void instruction_1F(cpu_t *cpu, mmu_t *mmu) { rra(cpu); }

// 0x2X
void instruction_20(cpu_t *cpu, mmu_t *mmu) { jr_e8(CC_NZ, cpu, mmu); }
void instruction_21(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_HL, cpu, mmu); }
void instruction_22(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_HLI, cpu, mmu); }
void instruction_23(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_HL, cpu); }
void instruction_24(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_H, cpu, mmu); }
void instruction_25(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_H, cpu, mmu); }
void instruction_26(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_H, cpu, mmu); }
void instruction_27(cpu_t *cpu, mmu_t *mmu) { daa(cpu); }
void instruction_28(cpu_t *cpu, mmu_t *mmu) { jr_e8(CC_Z, cpu, mmu); }
void instruction_29(cpu_t *cpu, mmu_t *mmu) { add_hl_r16(RT_HL, cpu, mmu); }
void instruction_2A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_HLI, cpu, mmu); }
void instruction_2B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_HL, cpu); }
void instruction_2C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_L, cpu, mmu); }
void instruction_2D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_L, cpu, mmu); }
void instruction_2E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_L, cpu, mmu); }
void instruction_2F(cpu_t *cpu, mmu_t *mmu) { cpl(cpu); }

// 0x3X
void instruction_30(cpu_t *cpu, mmu_t *mmu) { jr_e8(CC_NC, cpu, mmu); }
void instruction_31(cpu_t *cpu, mmu_t *mmu) { ld_r16_imm16(RT_SP, cpu, mmu); }
void instruction_32(cpu_t *cpu, mmu_t *mmu) { ld_r16mem_a(RT_HLD, cpu, mmu); }
void instruction_33(cpu_t *cpu, mmu_t *mmu) { inc_r16(RT_SP, cpu); }
void instruction_34(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_HL, cpu, mmu); }
void instruction_35(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_HL, cpu, mmu); }
void instruction_36(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_HL, cpu, mmu); }
void instruction_37(cpu_t *cpu, mmu_t *mmu) { scf(cpu); }
void instruction_38(cpu_t *cpu, mmu_t *mmu) { jr_e8(CC_C, cpu, mmu); }
void instruction_39(cpu_t *cpu, mmu_t *mmu) { add_hl_r16(RT_SP, cpu, mmu); }
void instruction_3A(cpu_t *cpu, mmu_t *mmu) { ld_a_r16mem(RT_HLD, cpu, mmu); }
void instruction_3B(cpu_t *cpu, mmu_t *mmu) { dec_r16(RT_SP, cpu); }
void instruction_3C(cpu_t *cpu, mmu_t *mmu) { inc_r8(RT_A, cpu, mmu); }
void instruction_3D(cpu_t *cpu, mmu_t *mmu) { dec_r8(RT_A, cpu, mmu); }
void instruction_3E(cpu_t *cpu, mmu_t *mmu) { ld_r8_imm8(RT_A, cpu, mmu); }
void instruction_3F(cpu_t *cpu, mmu_t *mmu) { ccf(cpu); }

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
void instruction_76(cpu_t *cpu, mmu_t *mmu) { halt(cpu); }
void instruction_77(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_HL, RT_A, cpu, mmu); }
void instruction_78(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_B, cpu, mmu); }
void instruction_79(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_C, cpu, mmu); }
void instruction_7A(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_D, cpu, mmu); }
void instruction_7B(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_E, cpu, mmu); }
void instruction_7C(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_H, cpu, mmu); }
void instruction_7D(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_L, cpu, mmu); }
void instruction_7E(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_HL, cpu, mmu); }
void instruction_7F(cpu_t *cpu, mmu_t *mmu) { ld_r8_r8(RT_A, RT_A, cpu, mmu); }

// 0x8X
void instruction_80(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_B, cpu, mmu); }
void instruction_81(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_C, cpu, mmu); }
void instruction_82(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_D, cpu, mmu); }
void instruction_83(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_E, cpu, mmu); }
void instruction_84(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_H, cpu, mmu); }
void instruction_85(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_L, cpu, mmu); }
void instruction_86(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_HL, cpu, mmu); }
void instruction_87(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_A, cpu, mmu); }
void instruction_88(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_B, cpu, mmu); }
void instruction_89(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_C, cpu, mmu); }
void instruction_8A(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_D, cpu, mmu); }
void instruction_8B(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_E, cpu, mmu); }
void instruction_8C(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_H, cpu, mmu); }
void instruction_8D(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_L, cpu, mmu); }
void instruction_8E(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_HL, cpu, mmu); }
void instruction_8F(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_A, cpu, mmu); }

// 0x9X
void instruction_90(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_B, cpu, mmu); }
void instruction_91(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_C, cpu, mmu); }
void instruction_92(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_D, cpu, mmu); }
void instruction_93(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_E, cpu, mmu); }
void instruction_94(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_H, cpu, mmu); }
void instruction_95(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_L, cpu, mmu); }
void instruction_96(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_HL, cpu, mmu); }
void instruction_97(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_A, cpu, mmu); }
void instruction_98(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_B, cpu, mmu); }
void instruction_99(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_C, cpu, mmu); }
void instruction_9A(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_D, cpu, mmu); }
void instruction_9B(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_E, cpu, mmu); }
void instruction_9C(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_H, cpu, mmu); }
void instruction_9D(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_L, cpu, mmu); }
void instruction_9E(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_HL, cpu, mmu); }
void instruction_9F(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_A, cpu, mmu); }

// 0xAX
void instruction_A0(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_B, cpu, mmu); }
void instruction_A1(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_C, cpu, mmu); }
void instruction_A2(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_D, cpu, mmu); }
void instruction_A3(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_E, cpu, mmu); }
void instruction_A4(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_H, cpu, mmu); }
void instruction_A5(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_L, cpu, mmu); }
void instruction_A6(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_HL, cpu, mmu); }
void instruction_A7(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_A, cpu, mmu); }
void instruction_A8(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_B, cpu, mmu); }
void instruction_A9(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_C, cpu, mmu); }
void instruction_AA(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_D, cpu, mmu); }
void instruction_AB(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_E, cpu, mmu); }
void instruction_AC(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_H, cpu, mmu); }
void instruction_AD(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_L, cpu, mmu); }
void instruction_AE(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_HL, cpu, mmu); }
void instruction_AF(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_A, cpu, mmu); }

// 0xBX
void instruction_B0(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_B, cpu, mmu); }
void instruction_B1(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_C, cpu, mmu); }
void instruction_B2(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_D, cpu, mmu); }
void instruction_B3(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_E, cpu, mmu); }
void instruction_B4(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_H, cpu, mmu); }
void instruction_B5(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_L, cpu, mmu); }
void instruction_B6(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_HL, cpu, mmu); }
void instruction_B7(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_A, cpu, mmu); }
void instruction_B8(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_B, cpu, mmu); }
void instruction_B9(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_C, cpu, mmu); }
void instruction_BA(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_D, cpu, mmu); }
void instruction_BB(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_E, cpu, mmu); }
void instruction_BC(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_H, cpu, mmu); }
void instruction_BD(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_L, cpu, mmu); }
void instruction_BE(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_HL, cpu, mmu); }
void instruction_BF(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_A, cpu, mmu); }

// 0xCX
void instruction_C0(cpu_t *cpu, mmu_t *mmu) { ret(CC_NZ, cpu, mmu); }
void instruction_C1(cpu_t *cpu, mmu_t *mmu) { pop_r16stk(RT_BC, cpu, mmu); }
void instruction_C2(cpu_t *cpu, mmu_t *mmu) { jp_addr16(CC_NZ, cpu, mmu); }
void instruction_C3(cpu_t *cpu, mmu_t *mmu) { jp_addr16(CC_NONE, cpu, mmu); }
void instruction_C4(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_NZ, cpu, mmu); }
void instruction_C5(cpu_t *cpu, mmu_t *mmu) { push_r16stk(RT_BC, cpu, mmu); }
void instruction_C6(cpu_t *cpu, mmu_t *mmu) { add_a_r8(RT_NONE, cpu, mmu); }
void instruction_C7(cpu_t *cpu, mmu_t *mmu) { rst(0x00, cpu, mmu); }
void instruction_C8(cpu_t *cpu, mmu_t *mmu) { ret(CC_Z, cpu, mmu); }
void instruction_C9(cpu_t *cpu, mmu_t *mmu) { ret(CC_NONE, cpu, mmu); }
void instruction_CA(cpu_t *cpu, mmu_t *mmu) { jp_addr16(CC_Z, cpu, mmu); }
void instruction_CC(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_Z, cpu, mmu); }
void instruction_CE(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_NONE, cpu, mmu); }
void instruction_CD(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_NONE, cpu, mmu); }
void instruction_CF(cpu_t *cpu, mmu_t *mmu) { rst(0x08, cpu, mmu); }

// 0xDX
void instruction_D0(cpu_t *cpu, mmu_t *mmu) { ret(CC_NC, cpu, mmu); }
void instruction_D1(cpu_t *cpu, mmu_t *mmu) { pop_r16stk(RT_DE, cpu, mmu); }
void instruction_D2(cpu_t *cpu, mmu_t *mmu) { jp_addr16(CC_NC, cpu, mmu); }
void instruction_D4(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_NC, cpu, mmu); }
void instruction_D5(cpu_t *cpu, mmu_t *mmu) { push_r16stk(RT_DE, cpu, mmu); }
void instruction_D6(cpu_t *cpu, mmu_t *mmu) { sub_a_r8(RT_NONE, cpu, mmu); }
void instruction_D7(cpu_t *cpu, mmu_t *mmu) { rst(0x10, cpu, mmu); }
void instruction_D8(cpu_t *cpu, mmu_t *mmu) { ret(CC_C, cpu, mmu); }
void instruction_D9(cpu_t *cpu, mmu_t *mmu) { reti(cpu, mmu); }
void instruction_DA(cpu_t *cpu, mmu_t *mmu) { jp_addr16(CC_C, cpu, mmu); }
void instruction_DC(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_C, cpu, mmu); }
void instruction_DE(cpu_t *cpu, mmu_t *mmu) { sbc_a_r8(RT_NONE, cpu, mmu); }
void instruction_DF(cpu_t *cpu, mmu_t *mmu) { rst(0x18, cpu, mmu); }

// 0xEX
void instruction_E0(cpu_t *cpu, mmu_t *mmu) { ldh_addr_a(RT_NONE, cpu, mmu); }
void instruction_E1(cpu_t *cpu, mmu_t *mmu) { pop_r16stk(RT_HL, cpu, mmu); }
void instruction_E2(cpu_t *cpu, mmu_t *mmu) { ldh_addr_a(RT_C, cpu, mmu); }
void instruction_E5(cpu_t *cpu, mmu_t *mmu) { push_r16stk(RT_HL, cpu, mmu); }
void instruction_E6(cpu_t *cpu, mmu_t *mmu) { and_a_r8(RT_NONE, cpu, mmu); }
void instruction_E7(cpu_t *cpu, mmu_t *mmu) { rst(0x20, cpu, mmu); }
void instruction_E8(cpu_t *cpu, mmu_t *mmu) { add_sp_e8(cpu, mmu); }
void instruction_E9(cpu_t *cpu, mmu_t *mmu) { jp_hl(cpu); }
void instruction_EA(cpu_t *cpu, mmu_t *mmu) { ld_addr16_a(cpu, mmu); }
void instruction_EE(cpu_t *cpu, mmu_t *mmu) { xor_a_r8(RT_NONE, cpu, mmu); }
void instruction_EF(cpu_t *cpu, mmu_t *mmu) { rst(0x28, cpu, mmu); }

// 0xFX
void instruction_F0(cpu_t *cpu, mmu_t *mmu) { ldh_a_addr(RT_NONE, cpu, mmu); }
void instruction_F1(cpu_t *cpu, mmu_t *mmu) { pop_r16stk(RT_AF, cpu, mmu); }
void instruction_F2(cpu_t *cpu, mmu_t *mmu) { ldh_a_addr(RT_C, cpu, mmu); }
void instruction_F3(cpu_t *cpu, mmu_t *mmu) { di(cpu); }
void instruction_F5(cpu_t *cpu, mmu_t *mmu) { push_r16stk(RT_AF, cpu, mmu); }
void instruction_F6(cpu_t *cpu, mmu_t *mmu) { or_a_r8(RT_NONE, cpu, mmu); }
void instruction_F7(cpu_t *cpu, mmu_t *mmu) { rst(0x30, cpu, mmu); }
void instruction_F8(cpu_t *cpu, mmu_t *mmu) { ld_hl_sp_plus_imm8(cpu, mmu); }
void instruction_F9(cpu_t *cpu, mmu_t *mmu) { ld_sp_hl(cpu, mmu); }
void instruction_FA(cpu_t *cpu, mmu_t *mmu) { ld_a_addr16(cpu, mmu); }
void instruction_FB(cpu_t *cpu, mmu_t *mmu) { ei(cpu); }
void instruction_FE(cpu_t *cpu, mmu_t *mmu) { cp_a_r8(RT_NONE, cpu, mmu); }
void instruction_FF(cpu_t *cpu, mmu_t *mmu) { rst(0x38, cpu, mmu); }

opfunc_t optable[0x100] = {
    // 0x0X
    [0x00] = instruction_00,
    [0x01] = instruction_01,
    [0x02] = instruction_02,
    [0x03] = instruction_03,
    [0x04] = instruction_04,
    [0x05] = instruction_05,
    [0x06] = instruction_06,
    [0x07] = instruction_07,
    [0x08] = instruction_08,
    [0x09] = instruction_09,
    [0x0A] = instruction_0A,
    [0x0B] = instruction_0B,
    [0x0C] = instruction_0C,
    [0x0D] = instruction_0D,
    [0x0E] = instruction_0E,
    [0x0F] = instruction_0F,

    // 0x1X
    [0x10] = instruction_10,
    [0x11] = instruction_11,
    [0x12] = instruction_12,
    [0x13] = instruction_13,
    [0x14] = instruction_14,
    [0x15] = instruction_15,
    [0x16] = instruction_16,
    [0x17] = instruction_17,
    [0x18] = instruction_18,
    [0x19] = instruction_19,
    [0x1A] = instruction_1A,
    [0x1B] = instruction_1B,
    [0x1C] = instruction_1C,
    [0x1D] = instruction_1D,
    [0x1E] = instruction_1E,
    [0x1F] = instruction_1F,

    // 0x2X
    [0x20] = instruction_20,
    [0x21] = instruction_21,
    [0x22] = instruction_22,
    [0x23] = instruction_23,
    [0x24] = instruction_24,
    [0x25] = instruction_25,
    [0x26] = instruction_26,
    [0x27] = instruction_27,
    [0x28] = instruction_28,
    [0x29] = instruction_29,
    [0x2A] = instruction_2A,
    [0x2B] = instruction_2B,
    [0x2C] = instruction_2C,
    [0x2D] = instruction_2D,
    [0x2E] = instruction_2E,
    [0x2F] = instruction_2F,

    // 0x3X
    [0x30] = instruction_30,
    [0x31] = instruction_31,
    [0x32] = instruction_32,
    [0x33] = instruction_33,
    [0x34] = instruction_34,
    [0x35] = instruction_35,
    [0x36] = instruction_36,
    [0x37] = instruction_37,
    [0x38] = instruction_38,
    [0x39] = instruction_39,
    [0x3A] = instruction_3A,
    [0x3B] = instruction_3B,
    [0x3C] = instruction_3C,
    [0x3D] = instruction_3D,
    [0x3E] = instruction_3E,
    [0x3F] = instruction_3F,

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

    // 0x8X
    [0x80] = instruction_80,
    [0x81] = instruction_81,
    [0x82] = instruction_82,
    [0x83] = instruction_83,
    [0x84] = instruction_84,
    [0x85] = instruction_85,
    [0x86] = instruction_86,
    [0x87] = instruction_87,
    [0x88] = instruction_88,
    [0x89] = instruction_89,
    [0x8A] = instruction_8A,
    [0x8B] = instruction_8B,
    [0x8C] = instruction_8C,
    [0x8D] = instruction_8D,
    [0x8E] = instruction_8E,
    [0x8F] = instruction_8F,

    // 0x9X
    [0x90] = instruction_90,
    [0x91] = instruction_91,
    [0x92] = instruction_92,
    [0x93] = instruction_93,
    [0x94] = instruction_94,
    [0x95] = instruction_95,
    [0x96] = instruction_96,
    [0x97] = instruction_97,
    [0x98] = instruction_98,
    [0x99] = instruction_99,
    [0x9A] = instruction_9A,
    [0x9B] = instruction_9B,
    [0x9C] = instruction_9C,
    [0x9D] = instruction_9D,
    [0x9E] = instruction_9E,
    [0x9F] = instruction_9F,

    // 0xAX
    [0xA0] = instruction_A0,
    [0xA1] = instruction_A1,
    [0xA2] = instruction_A2,
    [0xA3] = instruction_A3,
    [0xA4] = instruction_A4,
    [0xA5] = instruction_A5,
    [0xA6] = instruction_A6,
    [0xA7] = instruction_A7,
    [0xA8] = instruction_A8,
    [0xA9] = instruction_A9,
    [0xAA] = instruction_AA,
    [0xAB] = instruction_AB,
    [0xAC] = instruction_AC,
    [0xAD] = instruction_AD,
    [0xAE] = instruction_AE,
    [0xAF] = instruction_AF,

    // 0xBX
    [0xB0] = instruction_B0,
    [0xB1] = instruction_B1,
    [0xB2] = instruction_B2,
    [0xB3] = instruction_B3,
    [0xB4] = instruction_B4,
    [0xB5] = instruction_B5,
    [0xB6] = instruction_B6,
    [0xB7] = instruction_B7,
    [0xB8] = instruction_B8,
    [0xB9] = instruction_B9,
    [0xBA] = instruction_BA,
    [0xBB] = instruction_BB,
    [0xBC] = instruction_BC,
    [0xBD] = instruction_BD,
    [0xBE] = instruction_BE,
    [0xBF] = instruction_BF,

    // 0xCX
    [0xC0] = instruction_C0,
    [0xC1] = instruction_C1,
    [0xC2] = instruction_C2,
    [0xC3] = instruction_C3,
    [0xC4] = instruction_C4,
    [0xC5] = instruction_C5,
    [0xC6] = instruction_C6,
    [0xC7] = instruction_C7,
    [0xC8] = instruction_C8,
    [0xC9] = instruction_C9,
    [0xCA] = instruction_CA,
    [0xCC] = instruction_CC,
    [0xCD] = instruction_CD,
    [0xCF] = instruction_CF,

    // 0xDX
    [0xD0] = instruction_D0,
    [0xD1] = instruction_D1,
    [0xD2] = instruction_D2,
    [0xD4] = instruction_D4,
    [0xD5] = instruction_D5,
    [0xD6] = instruction_D6,
    [0xD7] = instruction_D7,
    [0xD8] = instruction_D8,
    [0xD9] = instruction_D9,
    [0xDA] = instruction_DA,
    [0xDC] = instruction_DC,
    [0xDE] = instruction_DE,
    [0xDF] = instruction_DF,

    // 0xEX
    [0xE0] = instruction_E0,
    [0xE1] = instruction_E1,
    [0xE2] = instruction_E2,
    [0xE5] = instruction_E5,
    [0xE6] = instruction_E6,
    [0xE7] = instruction_E7,
    [0xE8] = instruction_E8,
    [0xE9] = instruction_E9,
    [0xEA] = instruction_EA,
    [0xEE] = instruction_EE,
    [0xEF] = instruction_EF,

    // 0xFX
    [0xF0] = instruction_F0,
    [0xF1] = instruction_F1,
    [0xF2] = instruction_F2,
    [0xF3] = instruction_F3,
    [0xF5] = instruction_F5,
    [0xF6] = instruction_F6,
    [0xF7] = instruction_F7,
    [0xF8] = instruction_F8,
    [0xF9] = instruction_F9,
    [0xFA] = instruction_FA,
    [0xFB] = instruction_FB,
    [0xFE] = instruction_FE,
    [0xFF] = instruction_FF,
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
    [0x07] = "RLCA",
    [0x08] = "LD [a16], SP",
    [0x09] = "ADD HL, BC",
    [0x0A] = "LD A, [BC]",
    [0x0B] = "DEC BC",
    [0x0C] = "INC C",
    [0x0D] = "DEC C",
    [0x0E] = "LD C, n8",
    [0x0F] = "RRCA",

    // 0x1X
    [0x10] = "STOP",
    [0x11] = "LD DE, n16",
    [0x12] = "LD [DE], A",
    [0x13] = "INC DE",
    [0x14] = "INC D",
    [0x15] = "DEC D",
    [0x16] = "LD D, n8",
    [0x17] = "RLA",
    [0x18] = "JR e8",
    [0x19] = "ADD HL, DE",
    [0x1A] = "LD A, [DE]",
    [0x1B] = "DEC DE",
    [0x1C] = "INC E",
    [0x1D] = "DEC E",
    [0x1E] = "LD E, n8",
    [0x1F] = "RRA",

    // 0x2X
    [0x20] = "JR NZ, e8",
    [0x21] = "LD HL, n16",
    [0x22] = "LD [HL+], A",
    [0x23] = "INC HL",
    [0x24] = "INC H",
    [0x25] = "DEC H",
    [0x26] = "LD H, n8",
    [0x27] = "DAA",
    [0x28] = "JR Z, e8",
    [0x29] = "ADD HL, HL",
    [0x2A] = "LD A, [HLI]",
    [0x2B] = "DEC HL",
    [0x2C] = "INC L",
    [0x2D] = "DEC L",
    [0x2E] = "LD L, n8",
    [0x2F] = "CPL",

    // 0x3X
    [0x30] = "JR NC, e8",
    [0x31] = "LD SP, n16",
    [0x32] = "LD [HL-], A",
    [0x33] = "INC SP",
    [0x34] = "INC [HL]",
    [0x35] = "DEC [HL]",
    [0x36] = "LD [HL], n8",
    [0x37] = "SCF",
    [0x38] = "JR C, e8",
    [0x39] = "ADD HL, SP",
    [0x3A] = "LD A, [HLD]",
    [0x3B] = "DEC SP",
    [0x3C] = "INC A",
    [0x3D] = "DEC A",
    [0x3E] = "LD A, n8",
    [0x3F] = "CCF",

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
    [0x80] = "ADD A, B",
    [0x81] = "ADD A, C",
    [0x82] = "ADD A, D",
    [0x83] = "ADD A, E",
    [0x84] = "ADD A, H",
    [0x85] = "ADD A, L",
    [0x86] = "ADD A, [HL]",
    [0x87] = "ADD A, A",
    [0x88] = "ADC A, B",
    [0x89] = "ADC A, C",
    [0x8A] = "ADC A, D",
    [0x8B] = "ADC A, E",
    [0x8C] = "ADC A, H",
    [0x8D] = "ADC A, L",
    [0x8E] = "ADC A, [HL]",
    [0x8F] = "ADC A, A",

    // 0x9X
    [0x90] = "SUB A, B",
    [0x91] = "SUB A, C",
    [0x92] = "SUB A, D",
    [0x93] = "SUB A, E",
    [0x94] = "SUB A, H",
    [0x95] = "SUB A, L",
    [0x96] = "SUB A, [HL]",
    [0x97] = "SUB A, A",
    [0x98] = "SBC A, B",
    [0x99] = "SBC A, C",
    [0x9A] = "SBC A, D",
    [0x9B] = "SBC A, E",
    [0x9C] = "SBC A, H",
    [0x9D] = "SBC A, L",
    [0x9E] = "SBC A, [HL]",
    [0x9F] = "SBC A, A",

    // 0xAX
    [0xA0] = "AND A, B",
    [0xA1] = "AND A, C",
    [0xA2] = "AND A, D",
    [0xA3] = "AND A, E",
    [0xA4] = "AND A, H",
    [0xA5] = "AND A, L",
    [0xA6] = "AND A, [HL]",
    [0xA7] = "AND A, A",
    [0xA8] = "XOR A, B",
    [0xA9] = "XOR A, C",
    [0xAA] = "XOR A, D",
    [0xAB] = "XOR A, E",
    [0xAC] = "XOR A, H",
    [0xAD] = "XOR A, L",
    [0xAE] = "XOR A, [HL]",
    [0xAF] = "XOR A, A",

    // 0xBX
    [0xB0] = "OR A, B",
    [0xB1] = "OR A, C",
    [0xB2] = "OR A, D",
    [0xB3] = "OR A, E",
    [0xB4] = "OR A, H",
    [0xB5] = "OR A, L",
    [0xB6] = "OR A, [HL]",
    [0xB7] = "OR A, A",
    [0xB8] = "CP A, B",
    [0xB9] = "CP A, C",
    [0xBA] = "CP A, D",
    [0xBB] = "CP A, E",
    [0xBC] = "CP A, H",
    [0xBD] = "CP A, L",
    [0xBE] = "CP A, [HL]",
    [0xBF] = "CP A, A",

    // 0xCX
    [0xC0] = "RET NZ",
    [0xC1] = "POP BC",
    [0xC2] = "JP NZ, a16",
    [0xC3] = "JP a16",
    [0xC4] = "CALL NZ, a16",
    [0xC5] = "PUSH BC",
    [0xC6] = "ADD A, n8",
    [0xC7] = "RST 0x00",
    [0xC8] = "RET Z",
    [0xC9] = "RET",
    [0xCA] = "JP Z, a16",
    [0xCB] = "",
    [0xCC] = "CALL Z, a16",
    [0xCD] = "CALL a16",
    [0xCE] = "ADC A, n8",
    [0xCF] = "RST 0x08",

    // 0xDX
    [0xD0] = "RET NC",
    [0xD1] = "POP DE",
    [0xD2] = "JP NC, a16",
    [0xD4] = "CALL NC, a16",
    [0xD5] = "PUSH DE",
    [0xD6] = "SUB A, n8",
    [0xD7] = "RST 0x10",
    [0xD8] = "RET C",
    [0xD9] = "RETI",
    [0xDA] = "JP C, a16",
    [0xDC] = "CALL C, a16",
    [0xDE] = "SBC A, A",
    [0xDF] = "RST 0x18",

    // 0xEX
    [0xE0] = "LDH [a8], A",
    [0xE1] = "POP HL",
    [0xE2] = "LDH [C], A",
    [0xE5] = "PUSH HL",
    [0xE6] = "AND A, n8",
    [0xE7] = "RST 0x20",
    [0xE8] = "ADD SP, e8",
    [0xE9] = "JP HL",
    [0xEA] = "LD [a16], A",
    [0xEE] = "XOR A, n8",
    [0xEF] = "RST 0x28",

    // 0xFX
    [0xF0] = "LDH A, [a8]",
    [0xF1] = "POP AF",
    [0xF2] = "LDH A, [C]",
    [0xF3] = "DI",
    [0xF5] = "PUSH AF",
    [0xF6] = "OR A, n8",
    [0xF7] = "RST 0x30",
    [0xF8] = "LD HL, SP + e8",
    [0xF9] = "LD SP, HL",
    [0xFA] = "LD A, [a16]",
    [0xFB] = "EI",
    [0xFE] = "CP A, n8",
    [0xFF] = "RST 0x38",
};

char *get_instruction_string(uint8_t opcode) { return inst_to_string[opcode]; }

opfunc_t get_instruction(uint8_t opcode) { return optable[opcode]; }
