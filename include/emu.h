#pragma once

#include <mmu.h>
#include <stdint.h>

typedef struct {
  bool paused;
  bool die;
  uint64_t ticks;
} emu_context;

emu_context *get_emu_context();

int emu_run(int agrc, char **argv);

void emu_cycle(mmu_t *mmu);
