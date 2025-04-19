#include <dbg.h>
#include <stdio.h>

static char dbg_msg[1024] = {0};
static int msg_size = 0;

void dbg_update(mmu_t *mmu) {
  if (mmu_read(0xFF02, mmu) == 0x81) {
    char c = mmu_read(0xFF01, mmu);
    dbg_msg[msg_size++] = c;
    mmu_write(0xFF02, 0, mmu);
  }
}

void dbg_print() {
  if (dbg_msg[0]) {
    printf("DBG: %s\n", dbg_msg);
  }
}
