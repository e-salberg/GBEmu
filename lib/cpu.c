#include <cpu.h>
#include <cpu_opcodes.h>
#include <dbg.h>
#include <stdio.h>
#include <stdlib.h>

void check_and_handle_interrupts(cpu_t *cpu, mmu_t *mmu);

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
  if (!cpu->is_halted) {
    uint16_t start_pc = cpu->regs.pc;
    uint8_t opcode = mmu_read(cpu->regs.pc++, mmu);
    opfunc_t instruction = get_instruction(opcode);

    char flags[16];
    sprintf(flags, "%c%c%c%c", cpu->regs.f & (1 << 7) ? 'Z' : '-',
            cpu->regs.f & (1 << 6) ? 'N' : '-',
            cpu->regs.f & (1 << 5) ? 'H' : '-',
            cpu->regs.f & (1 << 4) ? 'C' : '-');

    char inst_str[16];
    get_instruction_string(opcode, inst_str, cpu, mmu);

    printf(
        "%04X: %-16s (%02X %02X %02X)  A: %02X F: %s BC: %02X%02X DE: %02X%02X "
        "HL: %02X%02X\n",
        start_pc, inst_str, opcode, mmu_read(cpu->regs.pc, mmu),
        mmu_read(cpu->regs.pc + 1, mmu), cpu->regs.a, flags, cpu->regs.b,
        cpu->regs.c, cpu->regs.d, cpu->regs.e, cpu->regs.h, cpu->regs.l);

    // execute instruction
    instruction(cpu, mmu);

    dbg_update(mmu);
    dbg_print();
  } else {
    // m-cycle
    if (mmu->interrupt_flag) {
      cpu->is_halted = false;
    }
  }

  if (cpu->ime) {
    // handle interrupts
    check_and_handle_interrupts(cpu, mmu);
    cpu->enabling_ime = false;
  }

  if (cpu->enabling_ime) {
    cpu->ime = true;
  }

  return true;
}

static bool check_interrupts(mmu_t *mmu, interrupt_t int_type) {
  return mmu->interrupt_flag & int_type && mmu->ie & int_type;
}

static void handle_interrupt(cpu_t *cpu, mmu_t *mmu, uint16_t addr,
                             interrupt_t int_type) {
  // 2 m-cycles?
  cpu->regs.sp--;
  mmu_write(cpu->regs.sp, (cpu->regs.pc >> 8) & 0xFF, mmu);
  // m-cycle
  cpu->regs.sp--;
  mmu_write(cpu->regs.sp, cpu->regs.pc & 0xFF, mmu);
  // m-cycle
  cpu->regs.pc = addr;
  mmu->interrupt_flag &= ~int_type;
  cpu->is_halted = false;
  cpu->ime = false;
}

void check_and_handle_interrupts(cpu_t *cpu, mmu_t *mmu) {
  if (check_interrupts(mmu, IT_VBLANK)) {
    handle_interrupt(cpu, mmu, 0x40, IT_VBLANK);
  }
  if (check_interrupts(mmu, IT_LCD_STAT)) {
    handle_interrupt(cpu, mmu, 0x48, IT_LCD_STAT);
  }
  if (check_interrupts(mmu, IT_TIMER)) {
    handle_interrupt(cpu, mmu, 0x50, IT_TIMER);
  }
  if (check_interrupts(mmu, IT_SERIAL)) {
    handle_interrupt(cpu, mmu, 0x58, IT_SERIAL);
  }
  if (check_interrupts(mmu, IT_JOYPAD)) {
    handle_interrupt(cpu, mmu, 0x60, IT_JOYPAD);
  }
}
