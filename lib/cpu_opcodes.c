#include "cpu.h"
#include <cpu_opcodes.h>
#include <stdio.h>

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
void instruction_CB(cpu_t *cpu, mmu_t *mmu) { cb(cpu, mmu); }
void instruction_CC(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_Z, cpu, mmu); }
void instruction_CD(cpu_t *cpu, mmu_t *mmu) { call_imm16(CC_NONE, cpu, mmu); }
void instruction_CE(cpu_t *cpu, mmu_t *mmu) { adc_a_r8(RT_NONE, cpu, mmu); }
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
    [0xCB] = instruction_CB,
    [0xCC] = instruction_CC,
    [0xCD] = instruction_CD,
    [0xCE] = instruction_CE,
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

void get_instruction_string(uint8_t opcode, char *str, cpu_t *cpu, mmu_t *mmu) {
  switch (opcode) {
  // 0x0X
  case 0x00:
    sprintf(str, "NOP");
    return;
  case 0x01:
    sprintf(str, "LD BC, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0x02:
    sprintf(str, "LD [BC], A");
    return;
  case 0x03:
    sprintf(str, "INC BC");
    return;
  case 0x04:
    sprintf(str, "INC B");
    return;
  case 0x05:
    sprintf(str, "DEC B");
    return;
  case 0x06:
    sprintf(str, "LD B, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x07:
    sprintf(str, "RLCA");
    return;
  case 0x08:
    sprintf(str, "LD [$%04X], SP", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x09:
    sprintf(str, "ADD HL, BC");
    return;
  case 0x0A:
    sprintf(str, "LD A, [BC]");
    return;
  case 0x0B:
    sprintf(str, "DEC BC");
    return;
  case 0x0C:
    sprintf(str, "INC C");
    return;
  case 0x0D:
    sprintf(str, "DEC C");
    return;
  case 0x0E:
    sprintf(str, "LD C, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x0F:
    sprintf(str, "RRCA");
    return;

  // 0x1X
  case 0x10:
    sprintf(str, "STOP");
    return;
  case 0x11:
    sprintf(str, "LD DE, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0x12:
    sprintf(str, "LD [DE], A");
    return;
  case 0x13:
    sprintf(str, "INC DE");
    return;
  case 0x14:
    sprintf(str, "INC D");
    return;
  case 0x15:
    sprintf(str, "DEC D");
    return;
  case 0x16:
    sprintf(str, "LD D, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x17:
    sprintf(str, "RLA");
    return;
  case 0x18:
    sprintf(str, "JR $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x19:
    sprintf(str, "ADD HL, DE");
    return;
  case 0x1A:
    sprintf(str, "LD A, [DE]");
    return;
  case 0x1B:
    sprintf(str, "DEC DE");
    return;
  case 0x1C:
    sprintf(str, "INC E");
    return;
  case 0x1D:
    sprintf(str, "DEC E");
    return;
  case 0x1E:
    sprintf(str, "LD E, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x1F:
    sprintf(str, "RRA");
    return;

  // 0x2X
  case 0x20:
    sprintf(str, "JR NZ, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x21:
    sprintf(str, "LD HL, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0x22:
    sprintf(str, "LD [HL+], A");
    return;
  case 0x23:
    sprintf(str, "INC HL");
    return;
  case 0x24:
    sprintf(str, "INC H");
    return;
  case 0x25:
    sprintf(str, "DEC H");
    return;
  case 0x26:
    sprintf(str, "LD H, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x27:
    sprintf(str, "DAA");
    return;
  case 0x28:
    sprintf(str, "JR Z, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x29:
    sprintf(str, "ADD HL, HL");
    return;
  case 0x2A:
    sprintf(str, "LD A, [HL+]");
    return;
  case 0x2B:
    sprintf(str, "DEC HL");
    return;
  case 0x2C:
    sprintf(str, "INC L");
    return;
  case 0x2D:
    sprintf(str, "DEC L");
    return;
  case 0x2E:
    sprintf(str, "LD L, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x2F:
    sprintf(str, "CPL");
    return;

  // 0x3X
  case 0x30:
    sprintf(str, "JR NC, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x31:
    sprintf(str, "LD SP, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0x32:
    sprintf(str, "LD [HL-], A");
    return;
  case 0x33:
    sprintf(str, "INC SP");
    return;
  case 0x34:
    sprintf(str, "INC [HL]");
    return;
  case 0x35:
    sprintf(str, "DEC [HL]");
    return;
  case 0x36:
    sprintf(str, "LD [HL], $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x37:
    sprintf(str, "SCF");
    return;
  case 0x38:
    sprintf(str, "JR C, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x39:
    sprintf(str, "ADD HL, SP");
    return;
  case 0x3A:
    sprintf(str, "LD A, [HL-]");
    return;
  case 0x3B:
    sprintf(str, "DEC SP");
    return;
  case 0x3C:
    sprintf(str, "INC A");
    return;
  case 0x3D:
    sprintf(str, "DEC A");
    return;
  case 0x3E:
    sprintf(str, "LD A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0x3F:
    sprintf(str, "CCF");
    return;

  // 0x4X
  case 0x40:
    sprintf(str, "LD B, B");
    return;
  case 0x41:
    sprintf(str, "LD B, C");
    return;
  case 0x42:
    sprintf(str, "LD B, D");
    return;
  case 0x43:
    sprintf(str, "LD B, E");
    return;
  case 0x44:
    sprintf(str, "LD B, H");
    return;
  case 0x45:
    sprintf(str, "LD B, L");
    return;
  case 0x46:
    sprintf(str, "LD B, [HL]");
    return;
  case 0x47:
    sprintf(str, "LD B, A");
    return;
  case 0x48:
    sprintf(str, "LD C, B");
    return;
  case 0x49:
    sprintf(str, "LD C, C");
    return;
  case 0x4A:
    sprintf(str, "LD C, D");
    return;
  case 0x4B:
    sprintf(str, "LD C, E");
    return;
  case 0x4C:
    sprintf(str, "LD C, H");
    return;
  case 0x4D:
    sprintf(str, "LD C, L");
    return;
  case 0x4E:
    sprintf(str, "LD C, [HL]");
    return;
  case 0x4F:
    sprintf(str, "LD C, A");
    return;

  // 0x5X
  case 0x50:
    sprintf(str, "LD D, B");
    return;
  case 0x51:
    sprintf(str, "LD D, C");
    return;
  case 0x52:
    sprintf(str, "LD D, D");
    return;
  case 0x53:
    sprintf(str, "LD D, E");
    return;
  case 0x54:
    sprintf(str, "LD D, H");
    return;
  case 0x55:
    sprintf(str, "LD D, L");
    return;
  case 0x56:
    sprintf(str, "LD D, [HL]");
    return;
  case 0x57:
    sprintf(str, "LD D, A");
    return;
  case 0x58:
    sprintf(str, "LD E, B");
    return;
  case 0x59:
    sprintf(str, "LD E, C");
    return;
  case 0x5A:
    sprintf(str, "LD E, D");
    return;
  case 0x5B:
    sprintf(str, "LD E, E");
    return;
  case 0x5C:
    sprintf(str, "LD E, H");
    return;
  case 0x5D:
    sprintf(str, "LD E, L");
    return;
  case 0x5E:
    sprintf(str, "LD E, [HL]");
    return;
  case 0x5F:
    sprintf(str, "LD E, A");
    return;

  // 0x6X
  case 0x60:
    sprintf(str, "LD H, B");
    return;
  case 0x61:
    sprintf(str, "LD H, C");
    return;
  case 0x62:
    sprintf(str, "LD H, D");
    return;
  case 0x63:
    sprintf(str, "LD H, E");
    return;
  case 0x64:
    sprintf(str, "LD H, H");
    return;
  case 0x65:
    sprintf(str, "LD H, L");
    return;
  case 0x66:
    sprintf(str, "LD H, [HL]");
    return;
  case 0x67:
    sprintf(str, "LD H, A");
    return;
  case 0x68:
    sprintf(str, "LD L, B");
    return;
  case 0x69:
    sprintf(str, "LD L, C");
    return;
  case 0x6A:
    sprintf(str, "LD L, D");
    return;
  case 0x6B:
    sprintf(str, "LD L, E");
    return;
  case 0x6C:
    sprintf(str, "LD L, H");
    return;
  case 0x6D:
    sprintf(str, "LD L, L");
    return;
  case 0x6E:
    sprintf(str, "LD L, [HL]");
    return;
  case 0x6F:
    sprintf(str, "LD L, A");
    return;

  // 0x7X
  case 0x70:
    sprintf(str, "LD [HL], B");
    return;
  case 0x71:
    sprintf(str, "LD [HL], C");
    return;
  case 0x72:
    sprintf(str, "LD [HL], D");
    return;
  case 0x73:
    sprintf(str, "LD [HL], E");
    return;
  case 0x74:
    sprintf(str, "LD [HL], H");
    return;
  case 0x75:
    sprintf(str, "LD [HL], L");
    return;
  case 0x76:
    sprintf(str, "HALT");
    return;
  case 0x77:
    sprintf(str, "LD [HL], A");
    return;
  case 0x78:
    sprintf(str, "LD A, B");
    return;
  case 0x79:
    sprintf(str, "LD A, C");
    return;
  case 0x7A:
    sprintf(str, "LD A, D");
    return;
  case 0x7B:
    sprintf(str, "LD A, E");
    return;
  case 0x7C:
    sprintf(str, "LD A, H");
    return;
  case 0x7D:
    sprintf(str, "LD A, L");
    return;
  case 0x7E:
    sprintf(str, "LD A, [HL]");
    return;
  case 0x7F:
    sprintf(str, "LD A, A");
    return;

  // 0x8X
  case 0x80:
    sprintf(str, "ADD A, B");
    return;
  case 0x81:
    sprintf(str, "ADD A, C");
    return;
  case 0x82:
    sprintf(str, "ADD A, D");
    return;
  case 0x83:
    sprintf(str, "ADD A, E");
    return;
  case 0x84:
    sprintf(str, "ADD A, H");
    return;
  case 0x85:
    sprintf(str, "ADD A, L");
    return;
  case 0x86:
    sprintf(str, "ADD A, [HL]");
    return;
  case 0x87:
    sprintf(str, "ADD A, A");
    return;
  case 0x88:
    sprintf(str, "ADC A, B");
    return;
  case 0x89:
    sprintf(str, "ADC A, C");
    return;
  case 0x8A:
    sprintf(str, "ADC A, D");
    return;
  case 0x8B:
    sprintf(str, "ADC A, E");
    return;
  case 0x8C:
    sprintf(str, "ADC A, H");
    return;
  case 0x8D:
    sprintf(str, "ADC A, L");
    return;
  case 0x8E:
    sprintf(str, "ADC A, [HL]");
    return;
  case 0x8F:
    sprintf(str, "ADC A, A");
    return;

  // 0x9X
  case 0x90:
    sprintf(str, "SUB A, B");
    return;
  case 0x91:
    sprintf(str, "SUB A, C");
    return;
  case 0x92:
    sprintf(str, "SUB A, D");
    return;
  case 0x93:
    sprintf(str, "SUB A, E");
    return;
  case 0x94:
    sprintf(str, "SUB A, H");
    return;
  case 0x95:
    sprintf(str, "SUB A, L");
    return;
  case 0x96:
    sprintf(str, "SUB A, [HL]");
    return;
  case 0x97:
    sprintf(str, "SUB A, A");
    return;
  case 0x98:
    sprintf(str, "SBC A, B");
    return;
  case 0x99:
    sprintf(str, "SBC A, C");
    return;
  case 0x9A:
    sprintf(str, "SBC A, D");
    return;
  case 0x9B:
    sprintf(str, "SBC A, E");
    return;
  case 0x9C:
    sprintf(str, "SBC A, H");
    return;
  case 0x9D:
    sprintf(str, "SBC A, L");
    return;
  case 0x9E:
    sprintf(str, "SBC A, [HL]");
    return;
  case 0x9F:
    sprintf(str, "SBC A, A");
    return;

  // 0xAX
  case 0xA0:
    sprintf(str, "AND A, B");
    return;
  case 0xA1:
    sprintf(str, "AND A, C");
    return;
  case 0xA2:
    sprintf(str, "AND A, D");
    return;
  case 0xA3:
    sprintf(str, "AND A, E");
    return;
  case 0xA4:
    sprintf(str, "AND A, H");
    return;
  case 0xA5:
    sprintf(str, "AND A, L");
    return;
  case 0xA6:
    sprintf(str, "AND A, [HL]");
    return;
  case 0xA7:
    sprintf(str, "AND A, A");
    return;
  case 0xA8:
    sprintf(str, "XOR A, B");
    return;
  case 0xA9:
    sprintf(str, "XOR A, C");
    return;
  case 0xAA:
    sprintf(str, "XOR A, D");
    return;
  case 0xAB:
    sprintf(str, "XOR A, E");
    return;
  case 0xAC:
    sprintf(str, "XOR A, H");
    return;
  case 0xAD:
    sprintf(str, "XOR A, L");
    return;
  case 0xAE:
    sprintf(str, "XOR A, [HL]");
    return;
  case 0xAF:
    sprintf(str, "XOR A, A");
    return;

  // 0xBX
  case 0xB0:
    sprintf(str, "OR A, B");
    return;
  case 0xB1:
    sprintf(str, "OR A, C");
    return;
  case 0xB2:
    sprintf(str, "OR A, D");
    return;
  case 0xB3:
    sprintf(str, "OR A, E");
    return;
  case 0xB4:
    sprintf(str, "OR A, H");
    return;
  case 0xB5:
    sprintf(str, "OR A, L");
    return;
  case 0xB6:
    sprintf(str, "OR A, [HL]");
    return;
  case 0xB7:
    sprintf(str, "OR A, A");
    return;
  case 0xB8:
    sprintf(str, "CP A, B");
    return;
  case 0xB9:
    sprintf(str, "CP A, C");
    return;
  case 0xBA:
    sprintf(str, "CP A, D");
    return;
  case 0xBB:
    sprintf(str, "CP A, E");
    return;
  case 0xBC:
    sprintf(str, "CP A, H");
    return;
  case 0xBD:
    sprintf(str, "CP A, L");
    return;
  case 0xBE:
    sprintf(str, "CP A, [HL]");
    return;
  case 0xBF:
    sprintf(str, "CP A, A");
    return;

  // 0xCX
  case 0xC0:
    sprintf(str, "RET NZ");
    return;
  case 0xC1:
    sprintf(str, "POP BC");
    return;
  case 0xC2:
    sprintf(str, "JP NZ, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xC3:
    sprintf(str, "JP $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xC4:
    sprintf(str, "CALL NZ, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xC5:
    sprintf(str, "PUSH BC");
    return;
  case 0xC6:
    sprintf(str, "ADD A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xC7:
    sprintf(str, "RST 0x00");
    return;
  case 0xC8:
    sprintf(str, "RET Z");
    return;
  case 0xC9:
    sprintf(str, "RET");
    return;
  case 0xCA:
    sprintf(str, "JP Z, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xCB:
    sprintf(str, "PERFIX");
    return;
  case 0xCC:
    sprintf(str, "CALL Z, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xCD:
    sprintf(str, "CALL $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xCE:
    sprintf(str, "ADC A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xCF:
    sprintf(str, "RST 0x08");
    return;

  // 0xDX
  case 0xD0:
    sprintf(str, "RET NC");
    return;
  case 0xD1:
    sprintf(str, "POP DE");
    return;
  case 0xD2:
    sprintf(str, "JP NC, %04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xD4:
    sprintf(str, "CALL NC, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xD5:
    sprintf(str, "PUSH DE");
    return;
  case 0xD6:
    sprintf(str, "SUB A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xD7:
    sprintf(str, "RST 0x10");
    return;
  case 0xD8:
    sprintf(str, "RET C");
    return;
  case 0xD9:
    sprintf(str, "RETI");
    return;
  case 0xDA:
    sprintf(str, "JP C, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xDC:
    sprintf(str, "CALL C, $%04X", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xDE:
    sprintf(str, "SBC A, A");
    return;
  case 0xDF:
    sprintf(str, "RST 0x18");
    return;

  // 0xEX
  case 0xE0:
    sprintf(str, "LDH [$%02X], A", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xE1:
    sprintf(str, "POP HL");
    return;
  case 0xE2:
    sprintf(str, "LDH [C], A");
    return;
  case 0xE5:
    sprintf(str, "PUSH HL");
    return;
  case 0xE6:
    sprintf(str, "AND A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xE7:
    sprintf(str, "RST 0x20");
    return;
  case 0xE8:
    sprintf(str, "AND SP, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xE9:
    sprintf(str, "JP HL");
    return;
  case 0xEA:
    sprintf(str, "LD [$%04X], A", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xEE:
    sprintf(str, "XOR A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xEF:
    sprintf(str, "RST 0x28");
    return;

  // 0xFX
  case 0xF0:
    sprintf(str, "LDH A, [$%04X]", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xF1:
    sprintf(str, "POP AF");
    return;
  case 0xF2:
    sprintf(str, "LDH A, [C]");
    return;
  case 0xF3:
    sprintf(str, "DI");
    return;
  case 0xF5:
    sprintf(str, "PUSH AF");
    return;
  case 0xF6:
    sprintf(str, "OR A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xF7:
    sprintf(str, "RST 0x30");
    return;
  case 0xF8:
    sprintf(str, "LD HL, SP + $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xF9:
    sprintf(str, "LD SP, HL");
    return;
  case 0xFA:
    sprintf(str, "LD A, [$%04X]", mmu_read16(cpu->regs.pc, mmu));
    return;
  case 0xFB:
    sprintf(str, "EI");
    return;
  case 0xFE:
    sprintf(str, "CP A, $%02X", mmu_read(cpu->regs.pc, mmu));
    return;
  case 0xFF:
    sprintf(str, "RST 0x38");
    return;
  default:
    return;
  };
}

opfunc_t get_instruction(uint8_t opcode) { return optable[opcode]; }
