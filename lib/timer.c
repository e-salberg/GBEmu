#include <interrupt.h>
#include <timer.h>

static timer_context timer_ctx = {0};

timer_context *get_timer_context() { return &timer_ctx; }

void timer_init() { timer_ctx.div = 0xAC00; }

void timer_tick(mmu_t *mmu) {
  uint16_t prev_div = timer_ctx.div;
  timer_ctx.div++;
  bool update_tima = false;
  uint8_t clock_select = timer_ctx.tac & 0b11;
  switch (clock_select) {
  case 0b00:
    update_tima = (prev_div & (1 << 9)) && (!(timer_ctx.div & (1 << 9)));
    break;
  case 0b01:
    update_tima = (prev_div & (1 << 3)) && (!(timer_ctx.div & (1 << 3)));
    break;
  case 0b10:
    update_tima = (prev_div & (1 << 5)) && (!(timer_ctx.div & (1 << 5)));
    break;
  case 0b11:
    update_tima = (prev_div & (1 << 7)) && (!(timer_ctx.div & (1 << 7)));
    break;
  }

  bool tac_enalbed = timer_ctx.tac & 0b100;
  if (update_tima && tac_enalbed) {
    timer_ctx.tima++;
    if (timer_ctx.tima == 0xFF) {
      timer_ctx.tima = timer_ctx.tma;
      request_interrupt(IT_TIMER, mmu);
    }
  }
}

void timer_write(uint16_t addr, uint8_t data) {
  switch (addr) {
  case 0xFF04:
    timer_ctx.div = 0;
    break;
  case 0xFF05:
    timer_ctx.tima = data;
    break;
  case 0xFF06:
    timer_ctx.tma = data;
    break;
  case 0xFF07:
    timer_ctx.tac = data;
    break;
  }
}

uint8_t timer_read(uint16_t addr) {
  switch (addr) {
  case 0xFF04:
    return timer_ctx.div >> 8;
  case 0xFF05:
    return timer_ctx.tima;
  case 0xFF06:
    return timer_ctx.tma;
  case 0xFF07:
    return timer_ctx.tac;
  default:
    return 0;
  }
}
