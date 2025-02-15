#include <bus.h>
#include <cartridge.h>

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

uint8_t read_bus(uint16_t address)
{
    if (address < 0x8000)
    {
        return read_cartridge(address);
    }
    else if (address < 0xA000)
    {
        
    }

}

void write_bus(uint16_t address, uint8_t value)
{
    if (address < 0x8000)
    {
        write_cartridge(address, value);
        return;
    }
}

uint16_t read16_bus(uint16_t address)
{
    uint16_t lo = read_bus(address);
    uint16_t hi = read_bus(address + 1);
    return (hi << 8) | lo;
}

void write16_bus(uint16_t address, uint16_t value)
{
    write_bus(address + 1, (value & 0xFF00) >> 8);
    write_bus(address, value & 0xFF); 
}