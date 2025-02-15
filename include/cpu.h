#include <stdint.h>
#include <stdbool.h>
#include <instructions.h>

typedef struct 
{
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
} cpu_registers;


typedef struct
{
    cpu_registers regs;
    uint8_t current_opcode;
    instruction *current_instruction;
    uint16_t fetched_data;
} cpu_context;

void cpu_init();
bool cpu_step();
cpu_registers *get_cpu_registers();

uint16_t read_register(reg_type rt);
void set_register(reg_type rt, uint16_t val);

typedef void (*instruction_function)(cpu_context *);
instruction_function get_instruction_function(instruction_type type);