#include <cartridge.h>
#include <cpu.h>
#include <mmu.h>
#include <stdio.h>

int emu_run(cpu_t *cpu, mmu_t *mmu);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Error: Need to provide a rom file\n");
    return -1;
  }

  cartridge_t *cartridge = cartridge_load(argv[1]);
  if (!cartridge) {
    printf("Failed to load cartridge");
    return -2;
  }

  mmu_t *mmu = mmu_init();
  mmu_load_rom(cartridge, mmu);

  cpu_t *cpu = cpu_init();

  return emu_run(cpu, mmu);
}

int emu_run(cpu_t *cpu, mmu_t *mmu) {
  while (true) {
    if (!cpu_step(cpu, mmu)) {
      printf("CPU Stopped\n");
      return -1;
    }
  }
  return 0;
}
