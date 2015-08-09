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
    tst r4, #0x80
    @eq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0]

    tst r4, #0x40
    @eq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x0180]

    tst r4, #0x20
    @eq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x0300]

    tst r4, #0x10
    @eq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x0480]

    tst r4, #0x08
    @nq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x0600]

    tst r4, #0x04
    @nq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x780]

    tst r4, #0x02
    @eq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x900]

    tst r4, #0x01
    @eq:  z=1, выключено
    it eq
    beq 1f
    mov r5, r2
    b 2f
1:  mov r5, r3
2:  strh r5, [r0, #0x0a80]


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

.global add_asm
.type add_asm, %function
add_asm:
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
