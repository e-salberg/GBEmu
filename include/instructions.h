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
    AM_A8_R,
    AM_R_A8,
    AM_A16_R,
    AM_R_A16,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_HLI,
    AM_R_HLD,
    AM_HL_SPE8,
    AM_SP_E8,
} addr_mode;

typedef enum {
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_LD_SP_E8,
    IN_LDH,
    IN_INC,
    IN_DEC,
    IN_JP,
    IN_JR,
    IN_CALL,
    IN_RET,
    IN_RETI,
    IN_RST,
    IN_PUSH,
    IN_POP,
    IN_ADD,
    IN_ADD_SP_E8,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_OR,
    IN_XOR,
    IN_CP,
    IN_RLCA,
    IN_RLA,
    IN_RRCA,
    IN_RRA,
    IN_EI,
    IN_DI,
    IN_HALT,
    IN_STOP,
    IN_CCF,
    IN_SCF,
    IN_DAA,
    IN_CPL,
    IN_CB,
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
    uint8_t param;
} instruction;

instruction *get_instruction_by_opcode(uint8_t opcode);

char *get_instruction_name(instruction_type t);