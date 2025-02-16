#include <cpu.h>
#include <bus.h>
#include <emu.h>
#include <instructions.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n); }

cpu_context ctx = {0};

static bool is_16_bit(reg_type rt)
{
    return rt > RT_AF;
}

static void set_flags(cpu_context *ctx, int8_t z, int8_t n, int8_t h, int8_t c)
{
    if (z != -1)
    {
        BIT_SET(ctx->regs.f, 7, z);
    }

    if (n != -1)
    {
        BIT_SET(ctx->regs.f, 6, n);
    }

    if (h != -1)
    {
        BIT_SET(ctx->regs.f, 5, h);
    }

    if (c != -1)
    {
        BIT_SET(ctx->regs.f, 4, c);
    }
}

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
    ctx.dest_in_memory = 0;
    ctx.is_dest_memory = false;
    uint8_t lo;
    uint8_t hi;

    switch(ctx.current_instruction->addr_mode)
    {   
        case AM_IMPLIED:
            break;
        case AM_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_1);
            break;
        case AM_MEMR:
            ctx.fetched_data = read_bus(read_register(ctx.current_instruction->reg_1));
            emu_cycles(1);
            ctx.dest_in_memory = read_register(ctx.current_instruction->reg_1);
            ctx.is_dest_memory = true;
            break;
        case AM_R_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_2);
            break;
        case AM_IMM16:
        case AM_R_IMM16:
            lo = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            hi = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            ctx.fetched_data = lo | (hi << 8);
            break;
        case AM_MEMR_IMM8:
            ctx.dest_in_memory = read_register(ctx.current_instruction->reg_1);
            ctx.is_dest_memory = true;
        case AM_R_IMM8:
            ctx.fetched_data = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            break;
        case AM_R_MEMR:
            ctx.fetched_data = read_bus(read_register(ctx.current_instruction->reg_2));
            emu_cycles(1);
            break;
        case AM_MEMR_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_2);
            ctx.dest_in_memory = read_register(ctx.current_instruction->reg_1);
            ctx.is_dest_memory = true;
            break;
        case AM_A16_R:
            lo = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            hi = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            ctx.dest_in_memory = (hi << 8) | lo;
            ctx.is_dest_memory = true;
            ctx.fetched_data = read_register(ctx.current_instruction->reg_1);
            break;
        case AM_R_A16:
            lo = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            hi = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            uint16_t addr = (hi << 8) | lo;
            ctx.fetched_data = read_bus(addr);
            emu_cycles(1);
            break;
        case AM_HLI_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_2);
            ctx.dest_in_memory = read_register(ctx.current_instruction->reg_1);
            ctx.is_dest_memory = true;
            set_register(RT_HL, read_register(RT_HL) + 1);
            break;
        case AM_HLD_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_2);
            ctx.dest_in_memory = read_register(ctx.current_instruction->reg_1);
            ctx.is_dest_memory = true;
            set_register(RT_HL, read_register(RT_HL) - 1);
            break;
        case AM_R_HLI:
            ctx.fetched_data = read_bus(read_register(RT_HL));
            emu_cycles(1);
            set_register(RT_HL, read_register(RT_HL) + 1);
            break;
        case AM_R_HLD:
            ctx.fetched_data = read_bus(read_register(RT_HL));
            emu_cycles(1);
            set_register(RT_HL, read_register(RT_HL) - 1);
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

    char flags[16];
    sprintf(flags, "%c%c%c%c", 
        ctx.regs.f & (1 << 7) ? 'Z' : '-',
        ctx.regs.f & (1 << 6) ? 'N' : '-',
        ctx.regs.f & (1 << 5) ? 'H' : '-',
        ctx.regs.f & (1 << 4) ? 'C' : '-'
    );

    printf("%04X: %-12s (%02X %02X %02X) A: %02X F: %s BC: %02X%02X DE: %02X%02X HL: %02X%02X\n", 
            pc, get_instruction_name(ctx.current_instruction->type), ctx.current_opcode,
            read_bus(pc + 1), read_bus(pc + 2), ctx.regs.a, flags, ctx.regs.b, ctx.regs.c,
            ctx.regs.d, ctx.regs.e, ctx.regs.h, ctx.regs.l);
    
    
    execute();
    return true;
}

static void nop(cpu_context *ctx)
{
    return;
}

static void load(cpu_context *ctx)
{
    if (ctx->is_dest_memory)
    {
        if (is_16_bit(ctx->current_instruction->reg_2))
        {
            emu_cycles(1);
            write16_bus(ctx->dest_in_memory, ctx->fetched_data);
        }
        else
        {
            write_bus(ctx->dest_in_memory, ctx->fetched_data);
        }
        emu_cycles(1);
        return;
    }
    set_register(ctx->current_instruction->reg_1, ctx->fetched_data);
}

static void increment(cpu_context *ctx)
{
    uint16_t data = ctx->fetched_data + 1;

    if (ctx->is_dest_memory)
    {  
        write_bus(ctx->dest_in_memory, data &= 0xFF);
        emu_cycles(1);
    }
    else
    {
        set_register(ctx->current_instruction->reg_1, data);
        if (is_16_bit(ctx->current_instruction->reg_1))
        {
            emu_cycles(1);
            return;
        }
    }
    set_flags(ctx, data == 0, 0, data & 0xF == 0, -1);
}

static void decrement(cpu_context *ctx)
{
    uint16_t data = ctx->fetched_data - 1;

    if (ctx->is_dest_memory)
    {  
        write_bus(ctx->dest_in_memory, data &= 0xFF);
        emu_cycles(1);
    }
    else
    {
        set_register(ctx->current_instruction->reg_1, data);
        if (is_16_bit(ctx->current_instruction->reg_1))
        {
            emu_cycles(1);
            return;
        }
    }
    set_flags(ctx, data == 0, 1, data & 0xF == 0xF, -1);
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
    [IN_INC] = increment,
    [IN_DEC] = decrement,
    [IN_JP] = jump,
};

instruction_function get_instruction_function(instruction_type type)
{
    return instr_functions[type];
}
