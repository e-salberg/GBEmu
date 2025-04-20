#include <interrupt.h>

void request_interrupt(interrupt_t int_type, mmu_t *mmu) {
  mmu->interrupt_flag |= int_type;
}
