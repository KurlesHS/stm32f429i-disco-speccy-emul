  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.include "Src/screen_macros.s"


.section .text
lines_addr:
    .word 0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00a0, 0x00c0, 0x00e0
    .word 0x0800, 0x0820, 0x0840, 0x0860, 0x0880, 0x08a0, 0x08c0, 0x08e0
    .word 0x1000, 0x1020, 0x1040, 0x1060, 0x1080, 0x10a0, 0x10c0, 0x10e0

.macro fill_8_bits_m
    @r0 lcd screen buff
    @r1 speccy screen addr
    @r2 set color
    @r3 res color
    ldrb r4,[r1]

    tst r4, #0x80

    @eq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0]

    tst r4, #0x40
    @eq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x0180]

    tst r4, #0x20
    @eq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x0300]

    tst r4, #0x10
    @eq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x0480]

    tst r4, #0x08
    @nq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x0600]

    tst r4, #0x04
    @nq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x780]

    tst r4, #0x02
    @eq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x900]

    tst r4, #0x01
    @eq:  z=1, выключено
    mov r5, r2
    it eq
    moveq r5, r3
    strh r5, [r0, #0x0a80]
.endm




.macro down_hl_m addr=r0, temp_reg=r1

    add \addr, #0x0100
    tst \addr, #0x0700
    bne 1f
    mov \temp_reg, \addr
    add \addr, \addr, #0x20
    and \temp_reg, \temp_reg, #0xff
    add \temp_reg, #0x20
    cmp \temp_reg, #0x100
    bcs 1f
    sub \addr, \addr, 0x0800
1:
.endm

.global line_addr
.type line_addr, %function
line_addr:
    mov r2, r0
    and r2, r2, #0xc0

    and r1, r0, #0x07
    lsl r1, r1, #0x03

    lsr r0, r0, #0x03
    and r0, r0, #0x07
    orr r0, r0, r1
    orr r0, r0, r2


.macro line_addr_m in_out, temp1, temp2
    mov temp1, in_out
    and temp1, temp1, #0xc0
    and temp2, in_out, #0x07
    lsl temp2, temp2, #0x03
    add in_out, in_out, #0x07
    orr in_out, in_out, temp1
    orr in_out, in_out, temp2
.endm

.global add_asm
.type add_asm, %function
add_asm:
    down_hl_m r0, r1
    add r0, r0, r1
    bx lr

.global fill_speccy_char
.type fill_speccy_char, %function

fill_speccy_char:
    @r0 = lcd scr
    @r1 = speccy byte addr
    @r2 = set color
    @r3 = res color
    @ldr r2, =#0xc0c0
    @mov r3,r2

    push {r0-r5}

    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m

    @ следующая линия
    sub r0, r0, #0x0002
    add r1, r1, #0x100
    fill_8_bits_m
    pop {r0-r5}
    bx lr


color_table:
    .short  0x0000, 0x0018, 0xc000, 0xc018
    .short  0x0600, 0x0600, 0x0600, 0xc618
    .short  0x0000, 0x001e, 0xf000, 0xf01e
    .short  0x0780, 0x0780, 0x0780, 0xf79e

.global update_screen
.type update_screen, %function
update_screen:
    @ r0: video buffer
    @ r1: speccy_screen_addr

    @ адрес атрибутов
    add r2, r1, #0x1800
    @ так как экран перевёрнут, добавляем 191 до точки, с кот. начнём вывод на экран
    add r0, r0, #382

    @ получаем цвета для inc и paper
    @ et_attr_color r_set_color, r_res_color, r_attr_addr, n_attr_offset, r_temp
    ldr r7, color_table
    get_attr_color r3, r4, r2, 0x00, r5
    @ пиксели
    ldrb r5, [r1]
    @ fill_8_bits screen_buff, bits, set_color, res_color, temp_res
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x01, r5
    ldrb r5, [r1, #0x01]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x02, r5
    ldrb r5, [r1, #0x02]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x03, r5
    ldrb r5, [r1, #0x03]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x04, r5
    ldrb r5, [r1, #0x04]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x05, r5
    ldrb r5, [r1, #0x05]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x06, r5
    ldrb r5, [r1, #0x06]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x07, r5
    ldrb r5, [r1, #0x07]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x08, r5
    ldrb r5, [r1, #0x08]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x09, r5
    ldrb r5, [r1, #0x09]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x0a, r5
    ldrb r5, [r1, #0x0a]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x0b, r5
    ldrb r5, [r1, #0x0b]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x0c, r5
    ldrb r5, [r1, #0x0c]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x0d, r5
    ldrb r5, [r1, #0x0d]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x0e, r5
    ldrb r5, [r1, #0x0e]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x0f, r5
    ldrb r5, [r1, #0x0f]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x10, r5
    ldrb r5, [r1, #0x10]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x11, r5
    ldrb r5, [r1, #0x11]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x12, r5
    ldrb r5, [r1, #0x12]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x13, r5
    ldrb r5, [r1, #0x13]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x14, r5
    ldrb r5, [r1, #0x14]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x15, r5
    ldrb r5, [r1, #0x15]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x16, r5
    ldrb r5, [r1, #0x16]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x17, r5
    ldrb r5, [r1, #0x17]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x18, r5
    ldrb r5, [r1, #0x18]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x19, r5
    ldrb r5, [r1, #0x19]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x1a, r5
    ldrb r5, [r1, #0x1a]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x1b, r5
    ldrb r5, [r1, #0x1b]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x1c, r5
    ldrb r5, [r1, #0x1c]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x1d, r5
    ldrb r5, [r1, #0x1d]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x1e, r5
    ldrb r5, [r1, #0x1e]
    fill_8_bits r0, r5, r3, r4, r6

    add r0, r0, #0x0c00
    get_attr_color r3, r4, r2, 0x1f, r5
    ldrb r5, [r1, #0x1f]
    fill_8_bits r0, r5, r3, r4, r6

    bx lr
