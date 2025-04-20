#pragma once

#include <mmu.h>

typedef enum {
  IT_VBLANK = 1,
  IT_LCD_STAT = 2,
  IT_TIMER = 4,
  IT_SERIAL = 8,
  IT_JOYPAD = 16,
} interrupt_t;

void request_interrupt(interrupt_t int_type, mmu_t *mmu);
