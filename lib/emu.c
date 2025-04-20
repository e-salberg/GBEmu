#include <cartridge.h>
#include <cpu.h>
#include <emu.h>
#include <mmu.h>
#include <stdio.h>
#include <timer.h>

static emu_context emu_ctx = {0};

emu_context *get_emu_context() { return &emu_ctx; }

int cpu_run(cpu_t *cpu, mmu_t *mmu) {
  emu_ctx.ticks = 0;
  while (true) {
    if (!cpu_step(cpu, mmu)) {
      printf("CPU Stopped\n");
      return -1;
    }
  }
  return 0;
}

int emu_run(int argc, char **argv) {
  if (argc < 2) {
    printf("Error: Need to provide a rom file\n");
    return -1;
  }

  cartridge_t *cartridge = cartridge_load(argv[1]);
  if (!cartridge) {
    printf("Failed to load cartridge");
    return -2;
  }

  timer_init();
  mmu_t *mmu = mmu_init();
  mmu_load_rom(cartridge, mmu);

  cpu_t *cpu = cpu_init();

  return cpu_run(cpu, mmu);
}

void emu_cycle(mmu_t *mmu) {
  for (int i = 0; i < 4; i++) {
    emu_ctx.ticks++;
    timer_tick(mmu);
  }
}
