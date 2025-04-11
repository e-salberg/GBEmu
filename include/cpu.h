#pragma once

#include <mmu.h>
#include <stdint.h>

#define CHECK_BIT(a, n) ((a & (1 << n)) ? 1 : 0)
#define SET_BIT(a, n, on)                                                      \
  {                                                                            \
    if (on)                                                                    \
      a |= (1 << n);                                                           \
    else                                                                       \
      a &= ~(1 << n);                                                          \
  }

typedef enum {
  RT_NONE,
  RT_A,
  RT_F,
  RT_B,
  RT_C,
  RT_D,
  RT_E,
  RT_H,
  RT_L,
  RT_AF,
  RT_BC,
  RT_DE,
  RT_HL,
  RT_SP,
  RT_PC,
} reg_type;

typedef struct {
  uint8_t a;
  uint8_t f;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t h;
  uint8_t l;
  uint16_t sp;
  uint16_t pc;
} registers_t;

typedef struct {
  registers_t regs;
} cpu_t;

cpu_t *cpu_init();

bool cpu_step(cpu_t *cpu, mmu_t *mmu);

uint16_t register_read(reg_type rt, cpu_t *cpu);
void register_set(reg_type rt, uint16_t val, cpu_t *cpu);

uint8_t register_read8(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void register_set8(reg_type rt, uint8_t val, cpu_t *cpu, mmu_t *mmu);

// CPU Instruction functions
void inc_r16(reg_type rt, cpu_t *cpu);
void inc_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu);
void dec_r16(reg_type rt, cpu_t *cpu);
void dec_r8(reg_type rt, cpu_t *cpu, mmu_t *mmu);
