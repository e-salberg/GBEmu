#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t entry_point[4]; // this is usually nops followed by jp 0x150
    uint8_t nintendo_logo[0x30];
    char title[16]; // this could be either 11 or 15 or 16 bytes
    //uint8_t manufacturer_code[4]; // this used to be part of title, newer carts have this
    //uint8_t cbg_flag; //CBG and later models used this byte to decide whether or not to enable Color mode
    uint16_t new_licensee_code;
    uint8_t sbg_flag;
    uint8_t cartridge_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;
    uint8_t old_licensee_code;
    uint8_t mask_rom_version;
    uint8_t header_checksum;
    uint16_t global_checksum;
} cartridge_header;

bool load_cartridge(char *cartridge);
void free_cartridge();

uint8_t read_cartridge(uint16_t address);
void write_cartridge(uint16_t address, uint8_t value);