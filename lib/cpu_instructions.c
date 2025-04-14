#include <cpu.h>
#include <cpu_opcodes.h>

static void set_flags(int8_t z, int8_t n, int8_t h, int8_t c, cpu_t *cpu) {
  if (z != -1) {
    SET_BIT(cpu->regs.f, 7, z);
  }
  if (n != -1) {
    SET_BIT(cpu->regs.f, 6, z);
  }
  if (h != -1) {
    SET_BIT(cpu->regs.f, 5, z);
  }
  if (c != -1) {
    SET_BIT(cpu->regs.f, 4, z);
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

  uint8_t h = (cpu->regs.sp & 0xF) + (data & 0xF) > 0xF;
  uint8_t c = (cpu->regs.sp & 0xFF) + data > 0xFF;
  // m-cycle

  // TODO - double check this logic
  // should be set L/get flags, cycle, set H
  register_set(RT_HL, cpu->regs.sp + data, cpu);
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
  uint8_t hi = mmu_read(cpu->regs.sp++, mmu);
  // m-cycle
  register_set(rt, (hi << 8) | lo, cpu);
  // TODO - how does this work with POP AF?
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
  int h = (hl & 0xFF) + (data & 0xFF) > 0xFF;
  set_flags(-1, 0, h, c, cpu);
}

// TODO - order should be set lsb(SP) -> m-cycle -> set msb(SP) -> m-cycle?
void add_sp_e8(cpu_t *cpu, mmu_t *mmu) {
  int8_t e = (int8_t)mmu_read(cpu->regs.pc++, mmu);
  // m-cycle
  uint16_t result = cpu->regs.sp + e;
  // m-cycle
  cpu->regs.sp = result;
  int c = (cpu->regs.sp + e) > 0xFFFF;
  int h = (cpu->regs.sp & 0xFF) + (e & 0xFF) > 0xFF;
  set_flags(0, 0, h, c, cpu);
  // m-cycle
}

void add_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data;
  if (rt == RT_NONE) {
    // RT_NONE means add a, imm8
    data = mmu_read(cpu->regs.pc++, mmu);
  } else {
    data = register_read8(rt, cpu, mmu);
  }
  if (rt == RT_HL || rt == RT_NONE) {
    // m-cycle
  }
  uint8_t result = cpu->regs.a + data;
  cpu->regs.a = result;

  int z = result == 0;
  int c = (cpu->regs.a + data) > 0xFF;
  int h = (cpu->regs.a & 0xF) + (data & 0xF) > 0xF;
  set_flags(z, 0, h, c, cpu);
}

void adc_a_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data;
  if (rt == RT_NONE) {
    data = mmu_read(cpu->regs.pc++, mmu);
  } else {
    data = register_read8(rt, cpu, mmu);
  }
  if (rt == RT_HL || rt == RT_NONE) {
    // m-cycle
  }
  int c = CHECK_BIT(cpu->regs.f, 4);
  uint8_t result = cpu->regs.a + data + c;
  cpu->regs.a = result;

  int h = (cpu->regs.a & 0xF) + (data & 0xF) + (c & 0xF) > 0xF;
  c = (cpu->regs.a + data + c) > 0xFF;
  set_flags(result == 0, 0, h, c, cpu);
}
