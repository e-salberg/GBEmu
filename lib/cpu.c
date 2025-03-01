#include <cpu.h>
#include <bus.h>
#include <emu.h>
#include <dbg.h>
#include <instructions.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

cpu_context ctx = {0};

void decode_opcode();

void cpu_init()
{
    ctx.regs.pc = 0x100;
    ctx.regs.sp = 0xFFFE;
    *((short *)&ctx.regs.a) = 0xB001;
    *((short *)&ctx.regs.b) = 0x1300;
    *((short *)&ctx.regs.d) = 0xD800;
    *((short *)&ctx.regs.h) = 0x4D01;
    ctx.interrupt_enable = 0;
    ctx.interrupt_master_enable = false;
    ctx.enabling_ime = false;
}

static void fetch_instruction()
{
    ctx.current_opcode = read_bus(ctx.regs.pc++);
    ctx.current_instruction = get_instruction_by_opcode(ctx.current_opcode);
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
    if (!ctx.is_halted)
    {    
        uint16_t pc = ctx.regs.pc;
        fetch_instruction();
        emu_cycles(1);
        decode_opcode();
        execute();

        char flags[16];
        sprintf(flags, "%c%c%c%c", 
            ctx.regs.f & (1 << 7) ? 'Z' : '-',
            ctx.regs.f & (1 << 6) ? 'N' : '-',
            ctx.regs.f & (1 << 5) ? 'H' : '-',
            ctx.regs.f & (1 << 4) ? 'C' : '-'
        );

        char inst[16];
        inst_to_str(&ctx, inst);

        printf("%04X: %-12s (%02X %02X %02X) A: %02X F: %s BC: %02X%02X DE: %02X%02X HL: %02X%02X\n", 
            pc, inst, ctx.current_opcode,
            read_bus(pc + 1), read_bus(pc + 2), ctx.regs.a, flags, ctx.regs.b, ctx.regs.c,
            ctx.regs.d, ctx.regs.e, ctx.regs.h, ctx.regs.l);

        dbg_update();
        dbg_print();        
    } 
    else 
    {
        emu_cycles(1);
        if (ctx.interrupt_flags)
        {
            ctx.is_halted = false;
        }

        if (ctx.interrupt_master_enable)
        {
            handle_cpu_interrupts(&ctx);
            ctx.enabling_ime = false;
        }

        if (ctx.enabling_ime)
        {
            ctx.interrupt_master_enable = true;
        }
    }
    return true;
}