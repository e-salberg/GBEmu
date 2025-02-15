#include <cpu.h>
#include <bus.h>
#include <emu.h>
#include <instructions.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

cpu_context ctx = {0};

void cpu_init()
{
    ctx.regs.pc = 0x100;
    ctx.regs.a = 0x01;
}

static void fetch_instruction()
{
    ctx.current_opcode = read_bus(ctx.regs.pc++);
    ctx.current_instruction = get_instruction_by_opcode(ctx.current_opcode);
}

static void decode_opcode()
{
    switch(ctx.current_instruction->addr_mode)
    {   
        case AM_IMPLIED:
            break;
        case AM_R8_R8:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_2);
            break;
        case AM_IMM16:
            uint8_t lo = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            uint8_t hi = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            ctx.fetched_data = lo | (hi << 8);
            break;
        default:
            printf("Unknown Addressing Mode! %d (%02X)\n", ctx.current_instruction->addr_mode, ctx.current_opcode);
            exit(-7);

    }
}

static void execute()
{
    instruction_function func = get_instruction_function(ctx.current_instruction->type);
    if (!func)
    {
        printf("Null Function returned!\n");
        exit(-8);
    }
    func(&ctx);
}

bool cpu_step()
{
    uint16_t pc = ctx.regs.pc;
    fetch_instruction();
    emu_cycles(1);
    decode_opcode();

    printf("%04X: %-7s (%02X %02X %02X) A: %02X B: %02X C: %02X\n", 
            pc, get_instruction_name(ctx.current_instruction->type), ctx.current_opcode,
            read_bus(pc + 1), read_bus(pc + 2), ctx.regs.a, ctx.regs.b, ctx.regs.c);
    
    
    execute();
    return true;
}

static void load(cpu_context *ctx)
{
    set_register(ctx->current_instruction->reg_1, ctx->fetched_data);
}

static void nop(cpu_context *ctx)
{
    return;
}

static void jump(cpu_context *ctx)
{
    ctx->regs.pc = ctx->fetched_data;
    emu_cycles(1);
}

static void none(cpu_context *ctx)
{
    printf("INVALID INSTRUCTION!\n");
    exit(-7);
}

static instruction_function instr_functions[] = {
    [IN_NONE] = none,
    [IN_NOP] = nop,
    [IN_LD] = load,
    [IN_JP] = jump,
};

instruction_function get_instruction_function(instruction_type type)
{
    return instr_functions[type];
}
