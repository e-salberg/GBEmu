#include <cpu.h>
#include <cpu_opcodes.h>
#include <stdio.h>
#include <stdlib.h>

cpu_t *cpu_init() {
  cpu_t *cpu = (cpu_t *)malloc(sizeof(cpu_t));
  cpu->regs.pc = 0x100;
  cpu->regs.sp = 0xFFFE;
  *((uint16_t *)&cpu->regs.a) = 0xB001;
  *((uint16_t *)&cpu->regs.b) = 0x1300;
  *((uint16_t *)&cpu->regs.d) = 0xD800;
  *((uint16_t *)&cpu->regs.h) = 0x4D01;
  return cpu;
}

bool cpu_step(cpu_t *cpu, mmu_t *mmu) {
  uint16_t start_pc = cpu->regs.pc;
  uint8_t opcode = mmu_read(cpu->regs.pc++, mmu);
  // printf("opcode %X\n", opcode);
  opfunc_t instruction = get_instruction(opcode);

  char flags[16];
  sprintf(flags, "%c%c%c%c", cpu->regs.f & (1 << 7) ? 'Z' : '-',
          cpu->regs.f & (1 << 6) ? 'N' : '-',
          cpu->regs.f & (1 << 5) ? 'H' : '-',
          cpu->regs.f & (1 << 4) ? 'C' : '-');

  char *inst_str = get_instruction_string(opcode);

  printf(
      "%04X: %-12s (%02X %02X %02X)\tA: %02X F: %s BC: %02X%02X DE: %02X%02X "
      "HL: %02X%02X\n",
      start_pc, inst_str, opcode, mmu_read(cpu->regs.pc, mmu),
      mmu_read(cpu->regs.pc + 1, mmu), cpu->regs.a, flags, cpu->regs.b,
      cpu->regs.c, cpu->regs.d, cpu->regs.e, cpu->regs.h, cpu->regs.l);

  // execute instruction
  instruction(cpu, mmu);
  return true;
}
