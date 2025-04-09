#pragma once

#include <stdint.h>

typedef struct {
  uint8_t rom_bank[2][0x4000];
  uint8_t vram[0x2000];
  uint8_t external_ram[0x2000];
  uint8_t wram[0x2000];
  uint8_t echo_ram[0x1E00];
  uint8_t oam[0xA0];
  uint8_t not_usable[0x60];
  uint8_t io_registers[0x80];
  uint8_t hram[0x80];
  uint8_t ie;
} mmu_t;

uint8_t mmu_read(mmu_t *mmu, uint16_t address);
void mmu_write(mmu_t *mmu, uint16_t address, uint8_t value);

uint16_t mmu_read16(mmu_t *mmu, uint16_t address);
void mmu_write16(mmu_t *mmu, uint16_t address, uint16_t value);
