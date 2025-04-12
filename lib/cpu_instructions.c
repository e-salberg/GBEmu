#include <cpu.h>

static void set_flags(cpu_t *cpu, int8_t z, int8_t n, int8_t h, int8_t c) {
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

void ld_r16_imm16(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t lo = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint8_t hi = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint16_t data = (hi << 8) | lo;
  register_set(rt, data, cpu);
}

void ld_r16mem_a(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = register_read(rt, cpu);
  mmu_write(mmu, addr, cpu->regs.a);
  // m-cycle

  if (rt == RT_HLI) {
    register_set(RT_HL, addr + 1, cpu);
  } else if (rt == RT_HLD) {
    register_set(RT_HL, addr - 1, cpu);
  }
}

void ld_a_r16mem(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint16_t addr = register_read(rt, cpu);
  uint8_t data = mmu_read(mmu, addr);
  // m-cycle
  register_set(RT_A, data, cpu);

  if (rt == RT_HLI) {
    register_set(RT_HL, addr + 1, cpu);
  } else if (rt == RT_HLD) {
    register_set(RT_HL, addr - 1, cpu);
  }
}

void ld_addr16_sp(cpu_t *cpu, mmu_t *mmu) {
  uint8_t lo = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint8_t hi = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint16_t addr = (hi << 8) | lo;
  mmu_write(mmu, addr, cpu->regs.sp & 0xFF);
  // m-cycle
  mmu_write(mmu, addr + 1, (cpu->regs.sp >> 8) & 0xFF);
  // m-cycle
}

void ld_addr16_a(cpu_t *cpu, mmu_t *mmu) {
  uint8_t lo = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint8_t hi = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint16_t addr = (hi << 8) | lo;
  mmu_write(mmu, addr, cpu->regs.a);
  // m-cycle
}

void ld_a_addr16(cpu_t *cpu, mmu_t *mmu) {
  uint8_t lo = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint8_t hi = mmu_read(mmu, cpu->regs.pc++);
  // m-cycle
  uint16_t addr = (hi << 8) | lo;
  uint8_t data = mmu_read(mmu, addr);
  // m-cycle
  cpu->regs.a = data;
}

void ld_r8_imm8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = mmu_read(mmu, cpu->regs.pc++);
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
  int8_t data = mmu_read(mmu, cpu->regs.pc++);
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

void inc_r16(reg_type rt, cpu_t *cpu) {
  uint16_t data = register_read(rt, cpu) + 1;
  register_set(rt, data, cpu);
}

void inc_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = register_read8(rt, cpu, mmu) + 1;
  register_set8(rt, data, cpu, mmu);
  set_flags(cpu, data == 0, 0, (data & 0xF) == 0, -1);
}

void dec_r16(reg_type rt, cpu_t *cpu) {
  uint16_t data = register_read(rt, cpu) - 1;
  register_set(rt, data, cpu);
}

void dec_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  uint8_t data = register_read8(rt, cpu, mmu) - 1;
  register_set8(rt, data, cpu, mmu);
  set_flags(cpu, data == 0, 1, (data & 0xF) == 0xF, -1);
}
