#pragma once

#include <stdint.h>

uint8_t read_io_registers(uint16_t address);
void  write_io_registers(uint16_t address, uint8_t data);