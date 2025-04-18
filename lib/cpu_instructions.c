#include <cpu.h>
#include <cpu_opcodes.h>
#include <stdio.h>
#include <stdlib.h>

static void set_flags(int8_t z, int8_t n, int8_t h, int8_t c, cpu_t *cpu) {
  if (z != -1) {
    SET_BIT(cpu->regs.f, 7, z);
  }
  if (n != -1) {
    SET_BIT(cpu->regs.f, 6, n);
  }
  if (h != -1) {
    SET_BIT(cpu->regs.f, 5, h);
  }
  if (c != -1) {
    SET_BIT(cpu->regs.f, 4, c);
  }
}

static bool check_condition(condition_code cond, cpu_t *cpu) {
  bool z = CHECK_BIT(cpu->regs.f, 7);
  bool c = CHECK_BIT(cpu->regs.f, 4);

  switch (cond) {
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

static uint16_t get_imm16_from_pc(cpu_t *cpu, mmu_t *mmu) {
  uint8_t lo = mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  uint8_t hi = mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  return (hi << 8) | lo;
}

static uint8_t get_r8_or_imm8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data;
  if (rt == RT_NONE) {
    data = mmu_read(cpu->regs.pc++, mmu);
  } else {
    data = register_read8(rt, cpu, mmu);
  }
  if (rt == RT_HL || rt == RT_NONE) {
    // m-cycle
  }
  return data;
}

void jp_addr16(condition_code cond, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = get_imm16_from_pc(cpu, mmu);
  if (check_condition(cond, cpu)) {
    cpu->regs.pc = addr;
    // m-cycle
  }
}

void jp_hl(cpu_t *cpu) { cpu->regs.pc = register_read(RT_HL, cpu); }

void jr_e8(condition_code cond, cpu_t *cpu, mmu_t *mmu) {
  int8_t e = (int8_t)mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  if (check_condition(cond, cpu)) {
    cpu->regs.pc += e;
    // m-cycle
  }
}

void call_imm16(condition_code cond, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = get_imm16_from_pc(cpu, mmu);

  if (check_condition(cond, cpu)) {
    cpu->regs.sp--;
    // m-cycle
    mmu_write(cpu->regs.sp, (cpu->regs.pc >> 8) & 0xFF, mmu);
    cpu->regs.sp--;
    // m-cycle
    mmu_write(cpu->regs.sp, cpu->regs.pc & 0xFF, mmu);
    // m-cycle
    cpu->regs.pc = addr;
  }
}

void ret(condition_code cond, cpu_t *cpu, mmu_t *mmu) {
  if (cond != CC_NONE) {
    // m-cycle
  }

  if (check_condition(cond, cpu)) {
    uint8_t lo = mmu_read(cpu->regs.sp++, mmu);
    // m-cycle
    uint8_t hi = mmu_read(cpu->regs.sp++, mmu);
    // m-cycle
    cpu->regs.pc = (hi << 8) | lo;
    // m-cycle
  }
}

void reti(cpu_t *cpu, mmu_t *mmu) {
  cpu->ime = true;
  ret(CC_NONE, cpu, mmu);
}

void rst(uint8_t addr, cpu_t *cpu, mmu_t *mmu) {
  cpu->regs.sp--;
  // m-cycle
  mmu_write(cpu->regs.sp, (cpu->regs.pc >> 8) & 0xFF, mmu);
  cpu->regs.sp--;
  // m-cycle
  mmu_write(cpu->regs.sp, cpu->regs.pc & 0xFF, mmu);
  // m-cycle
  cpu->regs.pc = addr;
}

void ld_r16_imm16(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t data = get_imm16_from_pc(cpu, mmu);
  register_set(rt, data, cpu);
}

void ld_r16mem_a(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = register_read(rt, cpu);
  mmu_write(addr, cpu->regs.a, mmu);
  // m-cycle

  if (rt == RT_HLI) {
    register_set(RT_HL, addr + 1, cpu);
  } else if (rt == RT_HLD) {
    register_set(RT_HL, addr - 1, cpu);
  }
}

void ld_a_r16mem(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = register_read(rt, cpu);
  uint8_t data = mmu_read(addr, mmu);
  // m-cycle
  register_set(RT_A, data, cpu);

  if (rt == RT_HLI) {
    register_set(RT_HL, addr + 1, cpu);
  } else if (rt == RT_HLD) {
    register_set(RT_HL, addr - 1, cpu);
  }
}

void ld_addr16_sp(cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = get_imm16_from_pc(cpu, mmu);
  mmu_write(addr, cpu->regs.sp & 0xFF, mmu);
  // m-cycle
  mmu_write(addr + 1, (cpu->regs.sp >> 8) & 0xFF, mmu);
  // m-cycle
}

void ld_addr16_a(cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = get_imm16_from_pc(cpu, mmu);
  mmu_write(addr, cpu->regs.a, mmu);
  // m-cycle
}

void ld_a_addr16(cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = get_imm16_from_pc(cpu, mmu);
  uint8_t data = mmu_read(addr, mmu);
  // m-cycle
  cpu->regs.a = data;
}

void ld_r8_imm8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  register_set8(rt, data, cpu, mmu);
}

void ld_r8_r8(reg_type dest, reg_type source, cpu_t *cpu, mmu_t *mmu) {
  if (source == dest) {
    // Loading a register into inself is a no-op
    return;
  }

  uint8_t data = register_read8(source, cpu, mmu);
  if (source == RT_HL) {
    // m-cycle
  }
  register_set8(dest, data, cpu, mmu);
  if (dest == RT_HL) {
    // m-cycle
  }
}

void ld_hl_sp_plus_imm8(cpu_t *cpu, mmu_t *mmu) {
  int8_t data = mmu_read(cpu->regs.pc++, mmu);
  // m-cycle

  int h = (cpu->regs.sp & 0xF) + (data & 0xF) > 0xF;
  int c = (cpu->regs.sp & 0xFF) + (data & 0xFF) > 0xFF;
  // m-cycle

  // TODO - double check this logic
  // should be set L/get flags, cycle, set H
  register_set(RT_HL, cpu->regs.sp + data, cpu);
  set_flags(0, 0, h, c, cpu);
}

void ld_sp_hl(cpu_t *cpu, mmu_t *mmu) {
  cpu->regs.sp = register_read(RT_HL, cpu);
  // m-cycle
}

void ldh_a_addr(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr;
  if (rt == RT_C) {
    addr = 0xFF00 | cpu->regs.c;
  } else {
    addr = 0xFF00 | mmu_read(cpu->regs.pc++, mmu);
    // m-cycle
  }
  cpu->regs.a = mmu_read(addr, mmu);
  // m-cycle
}

void ldh_addr_a(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr;
  if (rt == RT_C) {
    addr = 0xFF00 | cpu->regs.c;
  } else {
    addr = 0xFF00 | mmu_read(cpu->regs.pc++, mmu);
    // m-cycle
  }
  mmu_write(addr, cpu->regs.a, mmu);
  // m-cycle
}

void push_r16stk(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t data = register_read(rt, cpu);
  cpu->regs.sp--;
  // m-cycle
  mmu_write(cpu->regs.sp, (data >> 8) & 0xFF, mmu);
  cpu->regs.sp--;
  // m-cycle
  mmu_write(cpu->regs.sp, data & 0xFF, mmu);
  // m-cycle
}

void pop_r16stk(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t lo = mmu_read(cpu->regs.sp++, mmu);
  // m-cycle
  uint16_t hi = mmu_read(cpu->regs.sp++, mmu);
  // m-cycle
  uint16_t data = (hi << 8) | lo;
  register_set(rt, data, cpu);
  // TODO - how does this work with POP AF?
  if (rt == RT_AF) {
    register_set(rt, data & 0xFFF0, cpu);
  }
}

void inc_r16(reg_type rt, cpu_t *cpu) {
  uint16_t data = register_read(rt, cpu) + 1;
  register_set(rt, data, cpu);
}

void inc_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = register_read8(rt, cpu, mmu) + 1;
  register_set8(rt, data, cpu, mmu);
  set_flags(data == 0, 0, (data & 0xF) == 0, -1, cpu);
}

void dec_r16(reg_type rt, cpu_t *cpu) {
  uint16_t data = register_read(rt, cpu) - 1;
  register_set(rt, data, cpu);
}

void dec_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = register_read8(rt, cpu, mmu) - 1;
  register_set8(rt, data, cpu, mmu);
  set_flags(data == 0, 1, (data & 0xF) == 0xF, -1, cpu);
}

// TODO - order should add L + C, m-cycle, H + B + flags.c?
void add_hl_r16(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t hl = register_read(RT_HL, cpu);
  uint16_t data = register_read(rt, cpu);
  uint16_t result = hl + data;
  register_set(RT_HL, result, cpu);

  // m-cycle

  int c = (hl + data) > 0xFFFF;
  int h = (hl & 0xFFF) + (data & 0xFFF) > 0xFFF;
  set_flags(-1, 0, h, c, cpu);
}

// TODO - order should be set lsb(SP) -> m-cycle -> set msb(SP) -> m-cycle?
void add_sp_e8(cpu_t *cpu, mmu_t *mmu) {
  int8_t e = (int8_t)mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  uint16_t result = cpu->regs.sp + e;
  // m-cycle
  int c = (cpu->regs.sp & 0xFF) + (e & 0xFF) > 0xFF;
  int h = (cpu->regs.sp & 0xF) + (e & 0xF) > 0xF;
  cpu->regs.sp = result;
  set_flags(0, 0, h, c, cpu);
  // m-cycle
}

void add_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  uint8_t result = cpu->regs.a + data;

  int c = (cpu->regs.a + data) > 0xFF;
  int h = (cpu->regs.a & 0xF) + (data & 0xF) > 0xF;
  cpu->regs.a = result;
  set_flags(result == 0, 0, h, c, cpu);
}

void adc_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  int c = CHECK_BIT(cpu->regs.f, 4);
  uint8_t result = cpu->regs.a + data + c;

  int h = (cpu->regs.a & 0xF) + (data & 0xF) + (c & 0xF) > 0xF;
  c = (cpu->regs.a + data + c) > 0xFF;
  cpu->regs.a = result;
  set_flags(result == 0, 0, h, c, cpu);
}

void sub_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  uint8_t result = cpu->regs.a - data;

  int c = data > cpu->regs.a;
  int h = (data & 0xF) > (cpu->regs.a & 0xF);
  cpu->regs.a = result;
  set_flags(result == 0, 1, h, c, cpu);
}

void sbc_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  int c = CHECK_BIT(cpu->regs.f, 4);
  uint8_t result = cpu->regs.a - data - c;

  int h = (data & 0xF) + (c & 0xf) > (cpu->regs.a & 0xF);
  c = (data + c) > cpu->regs.a;
  cpu->regs.a = result;
  set_flags(result == 0, 1, h, c, cpu);
}

void and_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  cpu->regs.a &= data;
  set_flags(cpu->regs.a == 0, 0, 1, 0, cpu);
}

void xor_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  cpu->regs.a ^= data;
  set_flags(cpu->regs.a == 0, 0, 0, 0, cpu);
}

void or_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  cpu->regs.a |= data;
  set_flags(cpu->regs.a == 0, 0, 0, 0, cpu);
}

void cp_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = get_r8_or_imm8(rt, cpu, mmu);
  int z = (cpu->regs.a - data) == 0;
  int h = (data & 0xF) > (cpu->regs.a & 0xF);
  int c = data > cpu->regs.a;
  set_flags(z, 1, h, c, cpu);
}

void rlca(cpu_t *cpu) {
  bool c = CHECK_BIT(cpu->regs.a, 7);
  cpu->regs.a = (cpu->regs.a << 1) | c;
  set_flags(0, 0, 0, c, cpu);
}

void rla(cpu_t *cpu) {
  bool old_c = CHECK_BIT(cpu->regs.f, 4);
  bool c = CHECK_BIT(cpu->regs.a, 7);

  cpu->regs.a = (cpu->regs.a << 1) | old_c;
  set_flags(0, 0, 0, c, cpu);
}

void rrca(cpu_t *cpu) {
  bool c = CHECK_BIT(cpu->regs.a, 0);
  cpu->regs.a = (cpu->regs.a >> 1) | (c << 7);
  set_flags(0, 0, 0, c, cpu);
}

void rra(cpu_t *cpu) {
  bool old_c = CHECK_BIT(cpu->regs.f, 4);
  bool c = CHECK_BIT(cpu->regs.a, 0);
  cpu->regs.a = (cpu->regs.a >> 1) | (old_c << 7);
  set_flags(0, 0, 0, c, cpu);
}

// follows this logic https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7#DAA
void daa(cpu_t *cpu) {
  int cf = 0;
  bool c = CHECK_BIT(cpu->regs.f, 4);
  bool n = CHECK_BIT(cpu->regs.f, 6);
  bool h = CHECK_BIT(cpu->regs.f, 5);

  uint8_t adj = 0;
  if (h || (!n && (cpu->regs.a & 0xF) > 0x9)) {
    adj = 6;
  }
  if (c || (!n && cpu->regs.a > 0x99)) {
    adj |= 0x60;
    cf = 1;
  }
  cpu->regs.a += n ? -adj : adj;
  set_flags(cpu->regs.a == 0, -1, 0, cf, cpu);
  /*
    if (n) {
      if (h) {
        cpu->regs.a -= 0x6;
      }
      if (c) {
        cpu->regs.a -= 0x60;
      }
    } else {
      if (h || (cpu->regs.a & 0xF) > 0x9) {
        cpu->regs.a += 0x6;
      }
      if (c || cpu->regs.a > 0x99) {
        cpu->regs.a += 0x60;
        cf = 1;
      }
    }
    set_flags(cpu->regs.a == 0, -1, 0, cf, cpu);*/
}

void scf(cpu_t *cpu) { set_flags(-1, 0, 0, 1, cpu); }

void cpl(cpu_t *cpu) {
  cpu->regs.a = ~cpu->regs.a;
  set_flags(-1, 1, 1, -1, cpu);
}
void ccf(cpu_t *cpu) {
  int c = CHECK_BIT(cpu->regs.f, 4);
  set_flags(-1, 0, 0, c ^ 1, cpu);
}

void stop() {
  // TODO -
  // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
  printf("STOPPING");
  exit(-0x73746F70);
}

void halt(cpu_t *cpu) { cpu->is_halted = true; }

void ei(cpu_t *cpu) { cpu->enabling_ime = true; }

void di(cpu_t *cpu) { cpu->ime = false; }

/* ***CB Instructions*** */

static reg_type get_cb_operand(uint8_t operand) {
  switch (operand) {
  case 0x0:
    return RT_B;
  case 0x1:
    return RT_C;
  case 0x2:
    return RT_D;
  case 0x3:
    return RT_E;
  case 0x4:
    return RT_H;
  case 0x5:
    return RT_L;
  case 0x6:
    return RT_HL;
  case 0x7:
    return RT_A;
  default:
    return RT_NONE;
  }
}

void bit(uint8_t bit_index, reg_type rt, uint8_t data, cpu_t *cpu, mmu_t *mmu) {
  bool is_bit_set = ((1 << bit_index) & data);
  set_flags(!is_bit_set, 0, 1, -1, cpu);
}
void res(uint8_t bit_index, reg_type rt, uint8_t data, cpu_t *cpu, mmu_t *mmu) {
  data &= ~(1 << bit_index);
  register_set8(rt, data, cpu, mmu);
  if (rt == RT_HL) {
    // m-cycle
  }
}
void set(uint8_t bit_index, reg_type rt, uint8_t data, cpu_t *cpu, mmu_t *mmu) {
  data |= (1 << bit_index);
  register_set8(rt, data, cpu, mmu);
  if (rt == RT_HL) {
    // m-cycle
  }
}
void cb_block0(uint8_t opcode, reg_type rt, uint8_t data, cpu_t *cpu,
               mmu_t *mmu) {
  switch (opcode) {
  case 0b000: {
    // rlc r8
    bool c = CHECK_BIT(data, 7);
    uint8_t result = (data << 1) | c;
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  case 0b001: {
    // rrc r8
    bool c = CHECK_BIT(data, 7);
    uint8_t result = (data << 1) | c;
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  case 0b010: {
    // rl r8
    bool c = CHECK_BIT(data, 7);
    uint8_t result = (data << 1) | CHECK_BIT(cpu->regs.f, 4);
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  case 0b011: {
    // rr r8
    bool c = CHECK_BIT(data, 0);
    uint8_t result = (data >> 1) | (CHECK_BIT(cpu->regs.f, 4) << 7);
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  case 0b100: {
    // sla r8
    bool c = CHECK_BIT(data, 7);
    uint8_t result = (data << 1);
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  case 0b101: {
    // sra r8
    // bit7 of r8 is unchanged
    bool c = CHECK_BIT(data, 0);
    uint8_t bit7 = CHECK_BIT(data, 7);
    uint8_t result = (data >> 1) | (bit7 << 7);
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  case 0b110: {
    // swap r8
    uint8_t result = ((data & 0xF0) >> 4) | ((data & 0xF) << 4);
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    break;
  }
  case 0b111: {
    // srl r8
    bool c = CHECK_BIT(data, 0);
    uint8_t result = (data >> 1);
    register_set8(rt, result, cpu, mmu);
    if (rt == RT_HL) {
      // m-cycle
    }
    set_flags(result == 0, 0, 0, c, cpu);
    break;
  }
  default:
    break;
  }
}

void cb(cpu_t *cpu, mmu_t *mmu) {
  uint8_t cb_opcode = mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  reg_type operand = get_cb_operand(cb_opcode & 0b111);
  uint8_t data = get_r8_or_imm8(operand, cpu, mmu);
  uint8_t bit_index = (cb_opcode >> 3) & 0b111;

  switch (cb_opcode >> 6) {
  case 0b00:
    cb_block0(bit_index, operand, data, cpu, mmu);
    break;
  case 0b01:
    bit(bit_index, operand, data, cpu, mmu);
    break;
  case 0b10:
    res(bit_index, operand, data, cpu, mmu);
    break;
  case 0b11:
    set(bit_index, operand, data, cpu, mmu);
    break;
  }
}
