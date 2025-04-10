#include <cartridge.h>
#include <mmu.h>
#include <stdio.h>

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
  mmu_load_rom(mmu, cartridge);
}
