#include <cartridge.h>
#include <cpu.h>
#include <emu.h>
#include <stdlib.h>
#include <stdio.h>

static emu_context ctx;

emu_context *emu_get_context() 
{
    return &ctx;
}

int emu_run(int argc, char **argv) 
{
    if (argc < 2) 
    {
        printf("Error: Need to provide a rom file\n");
        return -1;
    }

    if (!load_cartridge(argv[1]))
    {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }
    printf("Cartridge loaded..\n");

    cpu_init();
    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;
    
    while (ctx.running)
    {
        if (ctx.paused)
        {
            // wait or something?
            continue;
        }

        if(!cpu_step())
        {
            printf("CPU Stopped\n");
            return 0;
        }
        ctx.ticks++;
    }

    free_cartridge();
    return 0;
}

void emu_cycles(int cpu_cycles)
{

}