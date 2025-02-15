#pragma once

#include <stdint.h>

uint8_t read_bus(uint16_t address);
void write_bus(uint16_t address, uint8_t value);

uint16_t read16_bus(uint16_t address);
void write16_bus(uint16_t address, uint16_t value);