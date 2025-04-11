#include <cpu.h>
#include <stdio.h>

uint16_t reverse(uint16_t n) {
  return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
}

uint16_t register_read(reg_type rt, cpu_t *cpu) {
  switch (rt) {
  case RT_A:
    return cpu->regs.a;
  case RT_F:
    return cpu->regs.f;
  case RT_B:
    return cpu->regs.b;
  case RT_C:
    return cpu->regs.c;
  case RT_D:
    return cpu->regs.d;
  case RT_E:
    return cpu->regs.e;
  case RT_H:
    return cpu->regs.h;
  case RT_L:
    return cpu->regs.l;
  case RT_AF:
    return reverse(*((uint16_t *)&cpu->regs.a));
  case RT_BC:
    return reverse(*((uint16_t *)&cpu->regs.b));
  case RT_DE:
    return reverse(*((uint16_t *)&cpu->regs.d));
  case RT_HL:
    return reverse(*((uint16_t *)&cpu->regs.h));
  case RT_SP:
    return reverse(*((uint16_t *)&cpu->regs.sp));
  case RT_PC:
    return reverse(*((uint16_t *)&cpu->regs.pc));
  default:
    return 0;
  }
}

void register_set(reg_type rt, uint16_t val, cpu_t *cpu) {
  switch (rt) {
  case RT_A:
    cpu->regs.a = val & 0xFF;
  case RT_F:
    cpu->regs.f = val & 0xFF;
  case RT_B:
    cpu->regs.b = val & 0xFF;
  case RT_C:
    cpu->regs.c = val & 0xFF;
  case RT_D:
    cpu->regs.d = val & 0xFF;
  case RT_E:
    cpu->regs.e = val & 0xFF;
  case RT_H:
    cpu->regs.h = val & 0xFF;
  case RT_L:
    cpu->regs.l = val & 0xFF;
  case RT_AF:
    *((uint16_t *)&cpu->regs.a) = reverse(val);
    break;
  case RT_BC:
    *((uint16_t *)&cpu->regs.b) = reverse(val);
    break;
  case RT_DE:
    *((uint16_t *)&cpu->regs.d) = reverse(val);
    break;
  case RT_HL:
    *((uint16_t *)&cpu->regs.h) = reverse(val);
    break;
  case RT_SP:
    cpu->regs.sp = val;
    break;
  case RT_PC:
    cpu->regs.pc = val;
    break;
  default:
    break;
  }
}

uint8_t register_read8(reg_type rt, cpu_t *cpu, mmu_t *mmu) {
  switch (rt) {
  case RT_B:
    return cpu->regs.b;
  case RT_C:
    return cpu->regs.c;
  case RT_D:
    return cpu->regs.d;
  case RT_E:
    return cpu->regs.e;
  case RT_H:
    return cpu->regs.h;
  case RT_L:
    return cpu->regs.l;
  case RT_HL:
    return mmu_read(mmu, register_read(RT_HL, cpu));
  case RT_A:
    return cpu->regs.a;
  default:
    printf("INVALID READ FOR REG8");
    return 0;
  }
}

void register_set8(reg_type rt, uint8_t val, cpu_t *cpu, mmu_t *mmu) {
  switch (rt) {
  case RT_B:
    cpu->regs.b = val;
    break;
  case RT_C:
    cpu->regs.c = val;
    break;
  case RT_D:
    cpu->regs.d = val;
    break;
  case RT_E:
    cpu->regs.e = val;
    break;
  case RT_H:
    cpu->regs.h = val;
    break;
  case RT_L:
    cpu->regs.l = val;
    break;
  case RT_HL:
    mmu_write(mmu, register_read(RT_HL, cpu), val);
    break;
  case RT_A:
    cpu->regs.a = val;
    break;
  default:
    printf("INVALID WRITE FOR REG8");
    break;
  }
}
