#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "speccy_hardware.h"

#include "stm32f4xx_hal.h"

#include "speccy_common.h"

void set_speccy_pixel(int current_line, int current_pixel, uint8_t color);

void gen_speccy_screen(speccy_hadrware *speccy);

#endif // SCREEN

