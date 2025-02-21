#include <cpu.h>
#include <instructions.h>
#include <bus.h>
#include <emu.h>

extern cpu_context ctx;

void decode_opcode()
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
        case AM_IMM8:
        case AM_R_IMM8:
        case AM_HL_SPE8:
        case AM_SP_E8:
            ctx.fetched_data = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            break;
        case AM_R_MEMR:
            uint16_t address = read_register(ctx.current_instruction->reg_2);
            if (ctx.current_instruction->reg_2 == RT_C)
            {
                address |= 0xFF00;
            }
            ctx.fetched_data = read_bus(address);
            emu_cycles(1);
            break;
        case AM_MEMR_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_2);
            ctx.dest_in_memory = read_register(ctx.current_instruction->reg_1);
            ctx.is_dest_memory = true;
            if (ctx.current_instruction->reg_1 == RT_C)
            {
                ctx.dest_in_memory |= 0xFF00;
            }
            break;
        case AM_A8_R:
            ctx.fetched_data = read_register(ctx.current_instruction->reg_1);
            ctx.dest_in_memory = read_bus(ctx.regs.pc++);
            ctx.is_dest_memory = true;
            emu_cycles(1);
            break;
        case AM_R_A8:
            uint8_t n = read_bus(ctx.regs.pc++);
            emu_cycles(1);
            ctx.fetched_data = read_bus(0xFF00 | n);
            emu_cycles(1);
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


static bool is_16_bit(reg_type rt)
{
    return rt > RT_AF;
}

static void set_flags(cpu_context *ctx, int8_t z, int8_t n, int8_t h, int8_t c)
{
    if (z != -1)
    {
        SET_BIT(ctx->regs.f, 7, z);
    }

    if (n != -1)
    {
        SET_BIT(ctx->regs.f, 6, n);
    }

    if (h != -1)
    {
        SET_BIT(ctx->regs.f, 5, h);
    }

    if (c != -1)
    {
        SET_BIT(ctx->regs.f, 4, c);
    }
}

static bool check_condition(cpu_context *ctx)
{
    bool z = CPU_FLAG_Z;
    bool c = CPU_FLAG_C;

    switch(ctx->current_instruction->cond)
    {
        case CC_NONE:
            return true;
        case CC_Z:
            return z;
        case CC_NZ:
            return !z;
        case CC_C:
            return c;
        case CC_NC:
            return !c;
    }
}

static void goto_address(cpu_context *ctx, uint16_t addr, bool pushpc)
{
    if (!check_condition(ctx))
    {
        return;
    }

    if (pushpc)
    {
        ctx->regs.sp--;
        emu_cycles(1);
        write_bus(ctx->regs.sp--, (ctx->regs.pc >> 8) & 0xFF);
        emu_cycles(1);
        write_bus(ctx->regs.sp, ctx->regs.pc & 0xFF);    
    }
    ctx->regs.pc = addr;
    emu_cycles(1);
}


static void nop(cpu_context *ctx)
{
    return;
}

static void ld(cpu_context *ctx)
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

// 0xF8 speical load LD HL, SP+e8
static void ld_sp_e8(cpu_context *ctx)
{
    uint8_t h = (ctx->regs.sp & 0xF) + (ctx->fetched_data & 0xF) > 0xF;
    uint8_t c =  (ctx->regs.sp & 0xFF) + (ctx->fetched_data & 0xFF) > 0xFF;
    set_register(ctx->current_instruction->reg_1, ((int8_t)ctx->fetched_data) + ctx->regs.sp);
    set_flags(ctx, 0, 0, h, c);
}

static void ldh(cpu_context *ctx)
{
    if (ctx->is_dest_memory)
    {
        write_bus(0xFF00 | ctx->dest_in_memory, ctx->fetched_data);
        emu_cycles(1);
    }
    else 
    {
        set_register(ctx->current_instruction->reg_1, ctx->fetched_data);
    }
}

static void inc(cpu_context *ctx)
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

static void dec(cpu_context *ctx)
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

static void jp(cpu_context *ctx)
{
    goto_address(ctx, ctx->fetched_data, false);
}

static void jr(cpu_context *ctx)
{
    int8_t rel = (int8_t)(ctx->fetched_data & 0xFF);
    uint16_t addr = ctx->regs.pc + rel;
    goto_address(ctx, addr, false);
}

static void call(cpu_context *ctx)
{
    goto_address(ctx, ctx->fetched_data, true);
}

static void ret(cpu_context *ctx)
{
    if (ctx->current_instruction->cond != CC_NONE)
    {
        emu_cycles(1);
    }

    if (check_condition(ctx))
    {
        uint8_t lo = read_bus(ctx->regs.sp++);
        emu_cycles(1);
        uint8_t hi = read_bus(ctx->regs.sp++);
        emu_cycles(1);
        ctx->regs.pc = (hi << 8) | lo;
        emu_cycles(1);
    }
}

static void reti(cpu_context *ctx)
{
    ctx->interrupt_master_enable = true;
    ret(ctx);
}

static void rst(cpu_context *ctx)
{
    goto_address(ctx, ctx->current_instruction->param, true);
}

static void push(cpu_context *ctx)
{
    ctx->regs.sp--;
    emu_cycles(1);
    write_bus(ctx->regs.sp--, (ctx->fetched_data >> 8) & 0xFF);
    emu_cycles(1);
    write_bus(ctx->regs.sp, ctx->fetched_data & 0xFF);   
    emu_cycles(1);
}

static void pop(cpu_context *ctx)
{  
    uint16_t lo = read_bus(ctx->regs.sp++);
    emu_cycles(1);
    uint16_t hi = read_bus(ctx->regs.sp++);
    emu_cycles(1);
    set_register(ctx->current_instruction->reg_1, (hi << 8) | lo);
}

static void add(cpu_context *ctx)
{
    // ADD HL, rr
    if (is_16_bit(ctx->current_instruction->reg_1))
    {
        uint16_t reg = read_register(ctx->current_instruction->reg_1);
        uint32_t result = reg + ctx->fetched_data;

        int c = result > 0xFFFF;
        int h = (reg & 0xFF) + (ctx->fetched_data & 0xFF) > 0xFF;

        // to be accuate for ADD HL, BC 
        // it should add L + C, m-cycle, H + B + flags.c?
        emu_cycles(1); 
        set_register(ctx->current_instruction->reg_1, result & 0xFFFF);
        set_flags(ctx, -1, 0, h, c);
    }
    else 
    {
        // ADD A, r or ADD A, n8
        uint8_t reg = read_register(ctx->current_instruction->reg_1) & 0xFF;
        uint8_t val = ctx->fetched_data & 0xFF;
        uint16_t result = reg + val;

        int z = result & 0xFF == 0;
        int c = result > 0xFF;
        int h = (reg & 0xF) + (ctx->fetched_data & 0xF) > 0xF;

        set_register(ctx->current_instruction->reg_1, result & 0xFF);
        set_flags(ctx, z, 0, h, c);
    }
}

static void add_sp_e8(cpu_context *ctx)
{
    int8_t e = (int8_t)ctx->fetched_data;
    uint16_t sp = read_register(RT_SP);

    uint32_t result = sp + e;

    int h = (sp & 0xF) + (e & 0xF) > 0xF;
    int c = (sp & 0xFF) + (e) > 0xFF;

    emu_cycles(1);
    set_register(RT_SP, result & 0xFFFF);
    emu_cycles(1);
    set_flags(ctx, 0, 0, h, c);
}

static void adc(cpu_context *ctx)
{
    uint16_t a = ctx->regs.a;
    uint16_t c = CPU_FLAG_C;
    uint16_t result = a + ctx->fetched_data + c;
    int h = (a & 0xF) + (ctx->fetched_data & 0xF) + (c & 0xF) > 0xF;

    set_register(RT_A, result);
    set_flags(ctx, ctx->regs.a == 0, 0, h, result > 0xFF);
}

static void sub(cpu_context *ctx)
{
    uint8_t reg = read_register(ctx->current_instruction->reg_1);
    uint8_t result = reg - ctx->fetched_data;
    int h = (ctx->fetched_data & 0xF) > (reg & 0xF);
    int c = ctx->fetched_data > reg;

    set_register(ctx->current_instruction->reg_1, result);
    set_flags(ctx, result == 0, 1, h, c);
}

static void sbc(cpu_context *ctx)
{
    uint8_t reg = read_register(ctx->current_instruction->reg_1);
    uint8_t cf = CPU_FLAG_C;
    uint8_t result = reg - ctx->fetched_data - cf;
    int h = (ctx->fetched_data & 0xF) + cf > (reg & 0xF);
    int c = (ctx->fetched_data + cf) > reg;

    set_register(ctx->current_instruction->reg_1, result);
    set_flags(ctx, result == 0, 1, h, c);
}

static void and(cpu_context *ctx)
{
    ctx->regs.a &= (ctx->fetched_data & 0xFF);
    set_flags(ctx, ctx->regs.a == 0, 0, 1, 0);
}

static void or(cpu_context *ctx)
{
    ctx->regs.a |= (ctx->fetched_data & 0xFF);
    set_flags(ctx, ctx->regs.a == 0, 0, 0, 0);
}

static void xor(cpu_context *ctx)
{
    ctx->regs.a ^= (ctx->fetched_data & 0xFF);
    set_flags(ctx, ctx->regs.a == 0, 0, 0, 0);
}

static void cp(cpu_context *ctx)
{
    uint8_t reg = read_register(ctx->current_instruction->reg_1);
    uint8_t result = reg - ctx->fetched_data;
    int h = (ctx->fetched_data & 0xF) > (reg & 0xF);
    int c = ctx->fetched_data > reg;
    set_flags(ctx, result == 0, 1, h, c);
}

static void rlca(cpu_context *ctx)
{
    bool c = CHECK_BIT(ctx->regs.a, 7);
    ctx->regs.a = (ctx->regs.a << 1) | c;
    set_flags(ctx, 0, 0, 0, c);
}

static void rla(cpu_context *ctx)
{
    bool c = CHECK_BIT(ctx->regs.a, 7);
    ctx->regs.a = (ctx->regs.a << 1) | CPU_FLAG_C;
    set_flags(ctx, 0, 0, 0, c);
}

static void rrca(cpu_context *ctx)
{
    uint8_t c = CHECK_BIT(ctx->regs.a, 0);
    ctx->regs.a = (ctx->regs.a >> 1) | (c << 7);
    set_flags(ctx, 0, 0, 0, c);
}

static void rra(cpu_context *ctx)
{
    uint8_t c = CHECK_BIT(ctx->regs.a, 0);
    ctx->regs.a = (ctx->regs.a >> 1) | (CPU_FLAG_C << 7);
    set_flags(ctx, 0, 0, 0, c);
}

static void ei(cpu_context *ctx)
{
    ctx->enabling_ime = true;
}

static void di(cpu_context *ctx)
{
    ctx->interrupt_master_enable = false;
}

static void halt(cpu_context *ctx)
{
    ctx->is_halted = true;
}

static void stop(cpu_context *ctx)
{
    fprintf(stderr, "STOPPING!\n");
    exit(-8);
}

static void ccf(cpu_context *ctx)
{
    set_flags(ctx, -1, 0, 0, CPU_FLAG_C ^ 1);
}

static void scf(cpu_context *ctx)
{
    set_flags(ctx, -1, 0, 0, 1);
}

static void daa(cpu_context *ctx)
{
    int c_flag = 0;
    if (CPU_FLAG_N)
    {
        // after a subtraction, only adjust if (half-)carry occurred
        if (CPU_FLAG_H)
        {
            ctx->regs.a -= 0x6;
        }
        if (CPU_FLAG_C)
        {
            ctx->regs.a -= 0x60;
        }
    }
    else 
    {
        // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (CPU_FLAG_H || ctx->regs.a & 0xF > 0x9)
        {
            ctx->regs.a += 0x6;
        }

        if (CPU_FLAG_C || ctx->regs.a > 0x99)
        {
            ctx->regs.a += 0x60;
            c_flag = 1;
        }
    }
    set_flags(ctx, ctx->regs.a == 0, -1, 0, c_flag);
}

static void cpl(cpu_context *ctx)
{   
    ctx->regs.a = ~ctx->regs.a;
    set_flags(ctx, -1, 1, 1, -1);
}

static reg_type get_cb_register(uint8_t operand)
{
    switch(operand)
    {
        case 0x00:
            return RT_B;
        case 0x01:
            return RT_C;
        case 0x02:
            return RT_D;
        case 0x03:
            return RT_E;
        case 0x04:
            return RT_H;
        case 0x05:
            return RT_L;
        case 0x06:
            return RT_HL;
        case 0x07:
            return RT_A;
        default:
            return RT_NONE;
    }
}

static void handle_single_operand_cb_instructions(cpu_context *ctx, uint8_t opcode, reg_type rt, uint8_t data)
{
    switch(opcode)
    {
        case 0b000:
            // rlc r8
            bool c = CHECK_BIT(data, 7);
            set_reg8(rt, (data << 1) | c);
            set_flags(ctx, read_reg8(rt) == 0, 0, 0, c);
            break;
        case 0b001:
            // rrc r8
            uint8_t c = CHECK_BIT(data, 0);
            set_reg8(rt, (data >> 1) | (c << 7));
            set_flags(ctx, read_reg8 == 0, 0, 0, c);
            break;
        case 0b010:
            // rl r8
            bool c = CHECK_BIT(data, 7);
            set_reg8(rt, (data << 1) | CPU_FLAG_C);
            set_flags(ctx, read_reg8(rt) == 0, 0, 0, c);
            break;
        case 0b11:
            // rr r8
            uint8_t c = CHECK_BIT(data, 0);
            set_reg8(rt, (data >> 1) | (CPU_FLAG_C << 7));
            set_flags(ctx, read_reg8(rt) == 0, 0, 0, c);
            break;
        case 0b100:
            // sla r8
            bool c = CHECK_BIT(data, 7);
            set_reg8(rt, data << 1);
            set_flags(ctx, read_reg8(rt) == 0, 0, 0, c);
            break;
        case 0b101:
            // sra r8
            // Shift Right Arithmetically register r8 (bit 7 of r8 is unchanged).
            bool c = CHECK_BIT(data, 0);
            uint8_t bit7 = CHECK_BIT(data, 7);
            set_reg8(rt, (data >> 1) | (bit7 << 7));
            set_flags(ctx, read_reg8(rt) == 0, 0, 0, c);
            break;
        case 0b110:
            // swap r8
            uint8_t result = ((data & 0xF0) >> 4) | ((data & 0xF) << 4);
            set_reg8(rt, result);
            set_flags(ctx, result == 0, 0, 0, 0);
            break;
        case 0b111:
            // srl r8
            bool c = CHECK_BIT(data, 0);
            set_reg8(rt, data >> 1);
            set_flags(ctx, read_reg8(rt) == 0, 0, 0, c);
            break;
        default:
            break;
    }
}

static void cb(cpu_context *ctx)
{
    uint8_t cb_instuction = ctx->fetched_data;
    uint8_t bit_index = (cb_instuction >> 3) & 0b111;
    reg_type reg = get_cb_register(cb_instuction & 0b111);
    uint8_t data = read_reg8(reg);
    switch ((cb_instuction >> 6))
    {   
        case 0b00:
            // single operand instructions
            handle_single_operand_cb_instructions(ctx, bit_index, reg, data);
            break;
        case 0b01:
            // bit b3, r8
            set_flags(ctx, !(data & (1 << bit_index)), 0, 1, -1);
            break;
        case 0b10:
            // res b3, r8
            data &= ~(1 << bit_index);
            set_reg8(reg, data);
            break;
        case 0b11:
            // set b3, r8
            data |= (1 << bit_index);
            set_reg8(reg, data);
            break;
        default:
            break;
    }
}

static void none(cpu_context *ctx)
{
    printf("INVALID INSTRUCTION!\n");
    exit(-7);
}

static instruction_function instr_functions[] = {
    [IN_NONE] = none,
    [IN_NOP] = nop,
    [IN_LD] = ld,
    [IN_LD_SP_E8] = ld_sp_e8,
    [IN_LDH] = ldh,
    [IN_INC] = inc,
    [IN_DEC] = dec,
    [IN_JP] = jp,
    [IN_JR] = jr,
    [IN_CALL] = call,
    [IN_RET] = ret,
    [IN_RETI] = reti,
    [IN_RST] = rst,
    [IN_PUSH] = push,
    [IN_POP] = pop,
    [IN_ADD] = add,
    [IN_ADD_SP_E8] = add_sp_e8,
    [IN_ADC] = adc,
    [IN_SUB] = sub,
    [IN_SBC] = sbc,
    [IN_AND] = and,
    [IN_OR] = or,
    [IN_XOR] = xor,
    [IN_CP] = cp,
    [IN_RLCA] = rlca,
    [IN_RLA] = rla,
    [IN_RRCA] = rrca,
    [IN_RRA] = rra,
    [IN_EI] = ei,
    [IN_DI] = di,
    [IN_HALT] = halt,
    [IN_STOP] = stop,
    [IN_CCF] = ccf,
    [IN_SCF] = scf,
    [IN_DAA] = daa,
    [IN_CPL] = cpl,
    [IN_CB] = cb,
};

instruction_function get_instruction_function(instruction_type type)
{
    return instr_functions[type];
}