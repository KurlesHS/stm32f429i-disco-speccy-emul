#include "screen.h"

#if 0
static void set_pixel(int x, int y, uint16_t pixel) {
    __IO uint16_t* addr = (uint16_t*)SCREEN_BUFFER_ADDR + y * 240 + x;
    if (addr <= (uint16_t*)SCREEN_BUFFER_ADDR) return;
    *addr = pixel;
}
#endif

/*
base 24 bit colors:
0x000000, 0x0000C0, 0xC00000, 0xC000C0, 0x00C000, 0x00C000, 0x0C000, 0xC0C0C0
0x000000, 0x0000F0, 0xF00000, 0xF000F0, 0x00F000, 0x00F000, 0x0F000, 0xF0F0F0
*/

static const uint16_t speccy_colors[] = {
    0x0000, 0x0018, 0xc000, 0xc018,
    0x0600, 0x0600, 0x0600, 0xc618,
    0x0000, 0x001e, 0xf000, 0xf01e,
    0x0780, 0x0780, 0x0780, 0xf79e
};

void set_speccy_pixel(int current_line, int current_pixel, uint8_t color)
{
    if (current_line >= 56 && current_line <= 296 && current_pixel >= 64 && current_pixel <= 384) {
        /* line as y */
        /* pixel sa x */
        /* set_pixel(current_line - 56, current_pixel - 64, speccy_colors[color]); */
        __IO uint16_t* addr = (uint16_t*)SCREEN_BUFFER_ADDR + (current_pixel - 64) * 240 + (current_line - 56);
        if (addr <= (uint16_t*)SCREEN_BUFFER_ADDR) return;
        *addr = speccy_colors[color];
    }
}

static inline void fill_8_bits(uint16_t *lcd_screen_addr, uint8_t bits, uint16_t set_color, uint16_t res_color) {
    *lcd_screen_addr = bits & 0x80 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x40 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x20 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x10 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x08 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x04 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x02 ? set_color : res_color;
    lcd_screen_addr += 192;
    *lcd_screen_addr = bits & 0x01 ? set_color : res_color;
}

static const uint16_t  scr_addr_offset_list[] = {
    0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00a0, 0x00c0, 0x00e0,
    0x0800, 0x0820, 0x0840, 0x0860, 0x0880, 0x08a0, 0x08c0, 0x08e0,
    0x1000, 0x1020, 0x1040, 0x1060, 0x1080, 0x10a0, 0x10c0, 0x10e0,
};

void gen_speccy_screen(speccy_hadrware *speccy)
{

    byte* attr_addr = speccy->z80_screen_addr + 0x1800;
    uint16_t *lcd_screen_addr = (uint16_t *)SCREEN_BUFFER_ADDR + 191;
    for (int row = 0; row < 24; ++row) {
        uint16_t *lcd_screen_addr_tmp = lcd_screen_addr - row * 8;
        byte* scr_addr = speccy->z80_screen_addr + scr_addr_offset_list[row];
        for (int column = 0; column < 32; ++column) {
            uint16_t set_color = speccy_colors[*attr_addr % 0x0f];
            uint16_t res_color = speccy_colors[(*attr_addr >> 0x04)];

            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            scr_addr += 0x100;
            fill_8_bits(lcd_screen_addr_tmp, *scr_addr, set_color, res_color);
            lcd_screen_addr_tmp--;
            /* сл. знакоместо */
            scr_addr -= 0x6ff;
            lcd_screen_addr_tmp += 192 * 8+8; /* 192 * 8 + 7 */
            ++attr_addr;
        }
    }
}
