  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb


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


  .global form_speccy_screen_asm
  .section  .text
  @.weak  Reset_Handler
  .type  form_speccy_screen_asm, %function
form_speccy_screen_asm:
    @ r0 - lcd_screen_buffer
    @ r1 - speccy_screen_addr
    ldrh  r2, [r1, r2, lsl #2]

    @ speccy attr area
    ldr r3, =0x1800
    add r3, r1, r3
    add r0, r0, #191


    fill_8_bits_m

    nop
    bx lr

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
    ldr r5, =main

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
