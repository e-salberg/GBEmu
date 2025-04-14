#pragma once

#include <cpu.h>
#include <mmu.h>

typedef enum { CC_NONE, CC_Z, CC_NZ, CC_C, CC_NC } condition_code;

typedef void (*opfunc_t)(cpu_t *cpu, mmu_t *mmu);

char *get_instruction_string(uint8_t opcode);
opfunc_t get_instruction(uint8_t opcode);

// CPU Instruction functions
void jp_addr16(condition_code cond, cpu_t *cpu, mmu_t *mmu);
void jp_hl(cpu_t *cpu);
void call_imm16(condition_code cond, cpu_t *cpu, mmu_t *mmu);
void ret(condition_code cond, cpu_t *cpu, mmu_t *mmu);
void reti(cpu_t *cpu, mmu_t *mmu);
void rst(uint8_t addr, cpu_t *cpu, mmu_t *mmu);

void ld_r16_imm16(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void ld_r16mem_a(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void ld_a_r16mem(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void ld_addr16_sp(cpu_t *cpu, mmu_t *mmu);
void ld_r8_imm8(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void ld_r8_r8(reg_type dest, reg_type source, cpu_t *cpu, mmu_t *mmu);
void ld_addr16_a(cpu_t *cpu, mmu_t *mmu);
void ld_a_addr16(cpu_t *cpu, mmu_t *mmu);
void ld_hl_sp_plus_imm8(cpu_t *cpu, mmu_t *mmu);
void ld_sp_hl(cpu_t *cpu, mmu_t *mmu);

void push_r16stk(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void pop_r16stk(reg_type rt, cpu_t *cpu, mmu_t *mmu);

void inc_r16(reg_type rt, cpu_t *cpu);
void inc_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void dec_r16(reg_type rt, cpu_t *cpu);
void dec_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu);
