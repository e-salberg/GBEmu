#pragma once

#include <cpu.h>
#include <mmu.h>

typedef enum { CC_NONE, CC_Z, CC_NZ, CC_C, CC_NC } condition_code;

typedef void (*opfunc_t)(cpu_t *cpu, mmu_t *mmu);

char *get_instruction_string(uint8_t opcode);
opfunc_t get_instruction(uint8_t opcode);
