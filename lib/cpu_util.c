#include <cpu.h>
#include <bus.h>

extern cpu_context ctx;

uint16_t reverse(uint16_t n)
{
    return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
}

cpu_registers *get_cpu_registers()
{
    return &ctx.regs;
}

uint8_t get_interrupt_enable()
{
    return ctx.interrupt_enable;
}

void set_interrupt_enable(uint8_t value)
{
    ctx.interrupt_enable = value;
}

uint8_t get_interrupt_flags()
{
    return ctx.interrupt_flags;
}

void set_interrupt_flags(uint8_t value)
{
    ctx.interrupt_flags = value;
}

void request_cpu_interrupt(interrupt_type type)
{
    ctx.interrupt_flags |= type;
}


static void int_handle(cpu_context *ctx, uint16_t address, interrupt_type type)
{
    write_bus(--get_cpu_registers()->sp, (ctx->regs.pc >> 8) & 0xFF);
    write_bus(--get_cpu_registers()->sp, ctx->regs.pc & 0xFF);
    ctx->regs.pc = address;
    ctx->interrupt_flags &= ~type;
    ctx->is_halted = false;
    ctx->interrupt_master_enable = false;
}

static bool int_check(cpu_context *ctx, interrupt_type type)
{
    return ctx->interrupt_flags & type && ctx->interrupt_enable & type;
}

void handle_cpu_interrupts(cpu_context *ctx)
{
    if (int_check(ctx, IT_VBLANK))
    {
        int_handle(ctx, 0x40, IT_VBLANK);
    }
    else if (int_check(ctx, IT_STAT)) 
    {
        int_handle(ctx, 0x48, IT_STAT);
    } 
    else if (int_check(ctx, IT_TIMER)) 
    {
        int_handle(ctx, 0x50, IT_TIMER);
    }  
    else if (int_check(ctx, IT_SERIAL)) 
    {
        int_handle(ctx, 0x58, IT_SERIAL);
    }  
    else if (int_check(ctx, IT_JOYPAD)) 
    {
        int_handle(ctx, 0x60, IT_JOYPAD);
    }
}

uint16_t read_register(reg_type rt)
{
    switch(rt)
    {
        case RT_A:
            return ctx.regs.a;
        case RT_F:
            return ctx.regs.f;
        case RT_B:
            return ctx.regs.b;
        case RT_C:
            return ctx.regs.c;
        case RT_D:
            return ctx.regs.d;
        case RT_E:
            return ctx.regs.e;
        case RT_H:
            return ctx.regs.h;
        case RT_L:
            return ctx.regs.l;
        case RT_AF:
            return reverse(*((uint16_t *)&ctx.regs.a));
        case RT_BC:
            return reverse(*((uint16_t *)&ctx.regs.b));
        case RT_DE:
            return reverse(*((uint16_t *)&ctx.regs.d));
        case RT_HL:
            return reverse(*((uint16_t *)&ctx.regs.h));
        case RT_SP:
            return reverse(*((uint16_t *)&ctx.regs.sp));
        case RT_PC:
            return reverse(*((uint16_t *)&ctx.regs.pc));
        default:
            return 0;
    }
}

void set_register(reg_type rt, uint16_t val)
{
    switch(rt)
    {
        case RT_A:
            ctx.regs.a = val & 0xFF;
            break;
        case RT_F:
            ctx.regs.f = val & 0xFF;
            break;
        case RT_B:
            ctx.regs.b = val & 0xFF;
            break;
        case RT_C:
            ctx.regs.c = val & 0xFF;
            break;
        case RT_D:
            ctx.regs.d = val & 0xFF;
            break;
        case RT_E:
            ctx.regs.e = val & 0xFF;
            break;
        case RT_H:
            ctx.regs.h = val & 0xFF;
            break;
        case RT_L:
            ctx.regs.l = val & 0xFF;
            break;
        case RT_AF:
            *((uint16_t *)&ctx.regs.a) = reverse(val);
            break;
        case RT_BC:
            *((uint16_t *)&ctx.regs.b) = reverse(val);
            break;
        case RT_DE:
            *((uint16_t *)&ctx.regs.d) = reverse(val);
            break;
        case RT_HL:
            *((uint16_t *)&ctx.regs.h) = reverse(val);
            break;
        case RT_PC:
            ctx.regs.pc = val;
            break;
        case RT_SP:
            ctx.regs.sp = val;
            break;
        default:
            break;
    }
}