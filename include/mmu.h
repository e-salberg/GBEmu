#pragma once

#include <cartridge.h>
#include <stdint.h>

typedef struct {
  // uint8_t rom_bank[2][0x4000];
  cartridge_t *cart;
  uint8_t vram[0x2000];
  // uint8_t external_ram[0x2000];
  uint8_t wram[0x2000];
  uint8_t echo_ram[0x1E00];
  uint8_t oam[0xA0];
  uint8_t not_usable[0x60];
  uint8_t io_registers[0x80];
  uint8_t hram[0x80];
  uint8_t ie;
  uint8_t interrupt_flag;

  uint8_t ly;
} mmu_t;

mmu_t *mmu_init();
void mmu_load_rom(cartridge_t *cartridge, mmu_t *mmu);

uint8_t mmu_read(uint16_t address, mmu_t *mmu);
void mmu_write(uint16_t address, uint8_t value, mmu_t *mmu);

uint16_t mmu_read16(uint16_t address, mmu_t *mmu);
void mmu_write16(uint16_t address, uint16_t value, mmu_t *mmu);
