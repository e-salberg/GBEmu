#pragma once

#include <mmu.h>
#include <stdint.h>

typedef struct {
  uint64_t emu_ticks;
  uint16_t div;
  uint8_t tima;
  uint8_t tma;
  uint8_t tac;
} timer_context;

void timer_init();
void timer_tick(mmu_t *mmu);

void timer_write(uint16_t addr, uint8_t data);
uint8_t timer_read(uint16_t addr);

timer_context *get_timer_context();
