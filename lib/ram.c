#include <ram.h>

typedef struct
{
    uint8_t wram[0x2000];
    uint8_t hram[0x80];
} ram_context;

static ram_context ctx;

uint8_t read_wram(uint16_t address)
{
    return ctx.wram[address - 0xC000];
}

void write_wram(uint16_t address, uint8_t value)
{
    ctx.wram[address - 0xC000] = value;
}

uint8_t read_hram(uint16_t address)
{
    return ctx.hram[address - 0xFF80];
}

void write_hram(uint16_t address, uint8_t value)
{
    ctx.hram[address - 0xFF80] = value;
}