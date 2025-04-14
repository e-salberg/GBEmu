#include <mmu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Memory Map
    0x0000 - 0x3FFF : 16 KiB ROM Bank 00 (Cartridge)
    0x4000 - 0x7FFF : 16 KiB ROM Bank 01 - NN (switchable)
    0x8000 - 0x9FFF : 8 KiB Video RAM (VRAM)
    0xA000 - 0xBFFF : 8 KiB External RAM (Cartridge)
    0xC000 - 0xCFFF : 4 KiB Work RAM (WRAM)
    0xD000 - 0xDFFF : 4 KiB Work RAM (WRAM) In CGB mode, switchable bank 1 - 7
    0xE000 - 0xFDFF : Reserved - Echo RAM (minor of 0xC000 - 0xDFFF)
    0xFE00 - 0xFE9F : Object Attribute Memory - OAM
    0xFEA0 - 0xFEFF : Reserved - Unusable
    0xFF00 - 0xFF7F : I/O Registers
    0xFF80 - 0xFFFE : High Ram (HRAM)
    0xFFFF - 0xFFFF : Interrupt Enable Register (IE)
*/

mmu_t *mmu_init() {
  mmu_t *mmu = (mmu_t *)malloc(sizeof(mmu_t));
  return mmu;
}

void mmu_load_rom(cartridge_t *cartridge, mmu_t *mmu) { mmu->cart = cartridge; }

uint8_t mmu_read(uint16_t address, mmu_t *mmu) {
  if (address < 0x4000) {
    // return mmu->rom_bank[0][address];
    return mmu->cart->rom_data[address];
  } else if (address < 0x8000) {
    // return mmu->rom_bank[1][address - 0x4000];
    return mmu->cart->rom_data[address];
  } else if (address < 0xA000) {
    return mmu->vram[address - 0x8000];
  } else if (address < 0xC000) {
    // return mmu->external_ram[address - 0xA000];
    return mmu->cart->rom_data[address];
  } else if (address < 0xE000) {
    return mmu->wram[address - 0xC000];
  } else if (address < 0xFE00) {
    // Reserved for Echo Ram
    return 0;
  } else if (address < 0xFEA0) {
    return mmu->oam[address - 0xFE00];
  } else if (address < 0xFF00) {
    // Reserved - Unusable
    return 0;
  } else if (address < 0xFF80) {
    return mmu->io_registers[address - 0xFF00];
  } else if (address < 0xFFFF) {
    return mmu->hram[address - 0xFF80];
  } else if (address == 0xFFFF) {
    return mmu->ie;
  }

  printf("INVALID READ %04X!\n", address);
  return 0;
}

void mmu_write(uint16_t address, uint8_t value, mmu_t *mmu) {
  if (address < 0x4000) {
    // mmu->rom_bank[0][address] = value;
    mmu->cart->rom_data[address] = value;
  } else if (address < 0x8000) {
    // mmu->rom_bank[1][address - 0x4000] = value;
    mmu->cart->rom_data[address] = value;
  } else if (address < 0xA000) {
    mmu->vram[address - 0x8000] = value;
  } else if (address < 0xC000) {
    // mmu->external_ram[address - 0xA000] = value;
    mmu->cart->rom_data[address] = value;
  } else if (address < 0xE000) {
    mmu->wram[address - 0xC000] = value;
  } else if (address < 0xFE00) {
    // Reserved for Echo Ram
  } else if (address < 0xFEA0) {
    mmu->oam[address - 0xFE00] = value;
  } else if (address < 0xFF00) {
    // Reserved - Unusable
  } else if (address < 0xFF80) {
    mmu->io_registers[address - 0xFF00] = value;
  } else if (address < 0xFFFF) {
    mmu->hram[address - 0xFF80] = value;
  } else if (address == 0xFFFF) {
    mmu->ie = value;
  } else {
    printf("INVALID WRITE %04X!\n", address);
  }
}

uint16_t mmu_read16(uint16_t address, mmu_t *mmu) {
  uint16_t lo = mmu_read(address, mmu);
  uint16_t hi = mmu_read(address + 1, mmu);
  return (hi << 8) | lo;
}

void mmu_write16(uint16_t address, uint16_t value, mmu_t *mmu) {
  mmu_write(address + 1, (value & 0xFF00) >> 8, mmu);
  mmu_write(address, value & 0xFF, mmu);
}
