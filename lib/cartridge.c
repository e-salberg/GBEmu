#include <cartridge.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t get_new_licensee_code_value(uint16_t code) {
  uint8_t hex_ascii_codes[2] = {code & 0xFF, code >> 8};

  uint8_t hi = (char)(hex_ascii_codes[0]) % 16;
  uint8_t lo = (char)(hex_ascii_codes[1]) % 16;
  return (hi * 16) + lo;
}

const char *get_cartridge_type_name(uint8_t type) {
  if (type > 0xFF) {
    return "UNKNOWN";
  }
  return CARTRIDGE_TYPES[type];
}

const char *get_cartridge_licensee_name(uint8_t old_code, uint16_t new_code) {
  if (old_code > 0xFF) {
    return "UNKNOWN";
  } else if (old_code == 0x33) {
    return NEW_LICENSEE_CODE[get_new_licensee_code_value(new_code)];
  }
  return OLD_LICENSEE_CODE[old_code];
}

cartridge_t *cartridge_load(char *filename) {
  cartridge_t *cart = NULL;
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    printf("Failed to open file: %s\n", filename);
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  uint32_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  if (size <= 0) {
    printf("File is empty");
    return NULL;
  }

  cart = (cartridge_t *)malloc(sizeof(cartridge_t));
  cart->rom_size = size;
  cart->rom_data = (uint8_t *)malloc(sizeof(uint8_t) * size);

  fread(cart->rom_data, size, 1, fp);
  fclose(fp);

  cart->header = (cartridge_header *)(cart->rom_data + 0x100);

  uint8_t licensee_code =
      cart->header->old_licensee_code == 0x33
          ? get_new_licensee_code_value(cart->header->new_licensee_code)
          : cart->header->old_licensee_code;

  printf("Cartridge Loaded:\n");
  printf("\t Title         : %s\n", cart->header->title);
  printf("\t Type          : %2.2X (%s)\n", cart->header->cartridge_type,
         get_cartridge_type_name(cart->header->cartridge_type));
  printf("\t SGB Flag      : %2.2X\n", cart->header->sbg_flag);
  printf("\t ROM Size      : %d KB\n", 32 << cart->header->rom_size);
  printf("\t RAM Size      : %2.2X\n", cart->header->ram_size);
  printf("\t Licensee Code : %2.2X (%s)\n", licensee_code,
         get_cartridge_licensee_name(cart->header->old_licensee_code,
                                     cart->header->new_licensee_code));
  printf("\t ROM Version   : %2.2X\n", cart->header->mask_rom_version);

  uint8_t checksum = 0;
  for (uint16_t address = 0x0134; address <= 0x014C; address++) {
    checksum = checksum - cart->rom_data[address] - 1;
  }

  printf("\t Checksum      : %2.2X (%s)\n", cart->header->header_checksum,
         (checksum & 0xFF) == cart->header->header_checksum ? "PASSED"
                                                            : "FAILED");

  return cart;
}

void cartridge_free(cartridge_t *cart) {
  if (cart) {
    free(cart->header);
    free(cart->rom_data);
    free(cart);
  }
}
