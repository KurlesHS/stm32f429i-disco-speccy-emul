#ifndef SPECCY_HARDWARE
#define SPECCY_HARDWARE

#include <z80/z80.h>

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif

typedef struct {
    byte *z80_page0_addr;
    byte *z80_page1_addr;
    byte *z80_page2_addr;
    byte *z80_page3_addr;

    byte *z80_screen_addr;

    uint16_t current_memory_bank;
    uint16_t current_screen_addr;
#if 0
    Bits 0-2: RAM page (0-7) to map into memory at 0xc000.

    Bit 3: Select normal (0) or shadow (1) screen to be displayed. The normal screen is in bank 5, whilst the shadow screen is in bank 7. Note that this does not affect the memory between 0x4000 and 0x7fff, which is always bank 5.

    Bit 4: ROM select. ROM 0 is the 128k editor and menu system; ROM 1 contains 48K BASIC.

    Bit 5: If set, memory paging will be disabled and further output to this port will be ignored until the computer is reset.
#endif
    uint8_t port_7ffd;
    /* 0 1 2 bits - border color, 3 4 bits - speaker */
    uint8_t port_fe;

    uint8_t current_border_color;

    Z80Context z80_context;

} speccy_hadrware;

/** Function type to emulate data read. */
byte read8_impl (void *param, ushort address);

/** Function type to emulate data write. */
void write8_impl (void *param, ushort address, byte data);


/** Function type to emulate data read. */
byte read8_io_port_impl (void *param, ushort address);

/** Function type to emulate data write. */
void write8_io_port_impl (void *param, ushort address, byte data);




void init_speccy_hardware(speccy_hadrware *hardware);

void speccy_frame(speccy_hadrware *hardware);


#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif


#endif // SPECCY_HARDWARE

