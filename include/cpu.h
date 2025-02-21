#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <instructions.h>

#define CHECK_BIT(a, n) ((a & (1 << n)) ? 1 : 0)
#define SET_BIT(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n); }

typedef struct 
{
    uint8_t a;
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
} cpu_registers;


typedef struct
{
    cpu_registers regs;
    uint8_t current_opcode;
    instruction *current_instruction;
    uint16_t fetched_data;
    uint16_t dest_in_memory;
    bool is_dest_memory;

    bool is_halted;
    bool interrupt_master_enable;
    bool enabling_ime;
    uint8_t interrupt_enable;
    uint8_t interrupt_flags;
} cpu_context;

typedef enum {
    IT_VBLANK = 1,
    IT_STAT = 2,
    IT_TIMER = 4,
    IT_SERIAL = 8,
    IT_JOYPAD = 16
} interrupt_type;

#define CPU_FLAG_Z CHECK_BIT(ctx->regs.f, 7)
#define CPU_FLAG_N CHECK_BIT(ctx->regs.f, 6)
#define CPU_FLAG_H CHECK_BIT(ctx->regs.f, 5)
#define CPU_FLAG_C CHECK_BIT(ctx->regs.f, 4)

void cpu_init();
bool cpu_step();
cpu_registers *get_cpu_registers();

uint16_t read_register(reg_type rt);
void set_register(reg_type rt, uint16_t val);

uint8_t read_reg8(reg_type rt);
void set_reg8(reg_type rt, uint8_t val);

typedef void (*instruction_function)(cpu_context *);
instruction_function get_instruction_function(instruction_type type);

uint8_t get_interrupt_enable();
void set_interrupt_enable(uint8_t val);

uint8_t get_interrupt_flags();
void set_interrupt_flags(uint8_t val);

void handle_cpu_interrupts(cpu_context *ctx);
void request_cpu_interrupt(interrupt_type type);