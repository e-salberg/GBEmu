#include <cartridge.h>
#include <emu.h>
#include <stdlib.h>
#include <stdio.h>


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

    free_cartridge();
    return 0;
}
