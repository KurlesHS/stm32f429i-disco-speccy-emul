#include <string.h>

#include "speccy_hardware.h"
#include "speccy_common.h"
#include "screen.h"


#include "kotuk.h"

static byte * const memory_banks[] = {
    (byte *)(SPECCY_MEMORY_START + 0x000000), (byte*)(SPECCY_MEMORY_START + 0x004000),
    (byte *)(SPECCY_MEMORY_START + 0x008000), (byte*)(SPECCY_MEMORY_START + 0x00c000),
    (byte *)(SPECCY_MEMORY_START + 0x010000), (byte*)(SPECCY_MEMORY_START + 0x014000),
    (byte *)(SPECCY_MEMORY_START + 0x018000), (byte*)(SPECCY_MEMORY_START + 0x01c000)
};

static byte * const rom_banks[] = {
    (byte *)(SPECCY_MEMORY_START + 0x020000), (byte*)(SPECCY_MEMORY_START + 0x024000)
};

inline static byte *real_addr_by_memory_bank(const uint16_t bank)
{
    return memory_banks[bank];
}

inline static byte *real_addr_by_rom_bank(const uint16_t bank)
{
    return rom_banks[bank];
}

byte read8_impl(void *param, ushort address)
{
    speccy_hadrware *hardware = (speccy_hadrware*)param;
    ushort offset = address & 0x3fff;
    ushort bank = address & 0xc000;
    byte *real_mem;
    switch (bank) {
    case 0x4000:
        real_mem = hardware->z80_page1_addr;
        break;
    case 0x8000:
        real_mem = hardware->z80_page2_addr;
        break;
    case 0xc000:
        real_mem = hardware->z80_page3_addr;
        break;
    default:
        real_mem = hardware->z80_page0_addr;
        break;
    }
    return *(real_mem + offset);
}

void write8_impl(void * param, ushort address, byte data)
{
    speccy_hadrware *hardware = (speccy_hadrware*)param;
    ushort offset = address & 0x3fff;
    ushort bank = address & 0xc000;
    byte *real_mem;
    switch (bank) {
    case 0x4000:
        real_mem = hardware->z80_page1_addr;
        break;
    case 0x8000:
        real_mem = hardware->z80_page2_addr;
        break;
    case 0xc000:
        real_mem = hardware->z80_page3_addr;
        break;
    default:
        // 0x0000 - read only
        return;
        break;
    }
    *(real_mem + offset) = data;
}

void init_speccy_hardware(speccy_hadrware *hardware)
{
    hardware->current_memory_bank = 0;
    hardware->current_border_color = 0;
    hardware->current_screen_addr = 0x4000;
    hardware->port_7ffd = 0x00;
    hardware->z80_page0_addr = real_addr_by_rom_bank(0);
    hardware->z80_page1_addr = real_addr_by_memory_bank(2);
    hardware->z80_page2_addr = real_addr_by_memory_bank(5);
    hardware->z80_page3_addr = real_addr_by_memory_bank(0);
    hardware->z80_screen_addr = real_addr_by_memory_bank(0);

    hardware->z80_context.memRead = read8_impl;
    hardware->z80_context.memWrite = write8_impl;
    hardware->z80_context.memParam = hardware;
    hardware->z80_context.ioParam = hardware;
    hardware->z80_context.int_vector = 0xff;

    memcpy(hardware->z80_screen_addr, kotuk_data, kotuk_data_len);

    Z80RESET(&hardware->z80_context);
}

static inline void render_tick(speccy_hadrware *hardware, register const int current_line, register const int current_pixel)
{
    if (current_line < 80 || current_line > 272) {
        set_speccy_pixel(current_line, current_pixel, hardware->current_border_color);
    }
}


void speccy_frame(speccy_hadrware *hardware)
{
    /* for now only pentagon timings */
    hardware->z80_context.int_req = 1;

    int current_line = 0;
    int current_pixel = hardware->z80_context.tstates * 2;
    int count = 0;

    Z80ExecuteTStates(&hardware->z80_context, 71680);
    return;

    while (1) {
        ++ count;
        unsigned prev_t_state = hardware->z80_context.tstates;
        Z80Execute(&hardware->z80_context);
        while (prev_t_state != hardware->z80_context.tstates) {
            render_tick(hardware, current_line, current_pixel++);
            if (current_pixel >= 448) {
                current_pixel = 0;
                ++current_line;
            }
            if (current_line == 320) {
                current_line = 0;
            }
            ++prev_t_state;
        }
        if (hardware->z80_context.tstates >= 71680) {
            hardware->z80_context.tstates -= 71680;
            break;
        }
    }
}


byte read8_io_port_impl(void *param, ushort address)
{
    (void)param;
    (void)address;
    return 0;
}


void write8_io_port_impl(void *param, ushort address, byte data)
{
    speccy_hadrware *hardware = (speccy_hadrware*)param;
    address &= 0xff;
    switch (address) {
    case 0xfe:
        hardware->port_fe = data;
        break;
    case 0xfd:
        hardware->port_7ffd = data;
        break;
    default:
        break;
    }
}
