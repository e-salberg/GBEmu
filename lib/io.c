#include <io.h>
#include <stdio.h>

static char serial_data[2];

uint8_t read_io_registers(uint16_t address)
{
    if (address == 0xFF01)
    {
        return serial_data[0];
    }
    else if (address == 0xFF02)
    {
        return serial_data[1];
    }

    printf("UNSUPPORTED BUS READ FOR IO REGISTERS: (%04X)\n", address);
    return 0;
}

void  write_io_registers(uint16_t address, uint8_t data)
{
    if (address == 0xFF01)
    {
        serial_data[0] = data;
    }
    else if (address == 0xFF02)
    {
        serial_data[1] = data;
    }

    printf("UNSUPPORTED BUS WRITE FOR IO REGISTERS: (%04X)\n", address);
}