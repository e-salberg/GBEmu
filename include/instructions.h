#pragma once

#include <stdint.h>

typedef enum {
    RT_NONE,
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC
} reg_type;

typedef enum {
    AM_IMPLIED,
    AM_IMM8,
    AM_IMM16,
    AM_R,
    AM_MEMR,
    AM_R_R,
    AM_R_IMM16,
    AM_R_IMM8,
    AM_R_MEMR,
    AM_MEMR_R,
    AM_MEMR_IMM8,
    AM_A16_R,
    AM_R_A16,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_HLI,
    AM_R_HLD,
} addr_mode;

typedef enum {
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_JP,
    IN_JR,
    IN_CALL,
    IN_RET,
    IN_RETI,
} instruction_type;

typedef enum {
    CC_NONE,
    CC_Z,
    CC_NZ,
    CC_C,
    CC_NC
} condition_code;


typedef struct {
    instruction_type type;
    addr_mode addr_mode;
    reg_type reg_1;
    reg_type reg_2;
    condition_code cond;
} instruction;

instruction *get_instruction_by_opcode(uint8_t opcode);

char *get_instruction_name(instruction_type t);