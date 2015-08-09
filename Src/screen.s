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
    strh r1, [r3, 4], LSR #16

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

    nop
    bx lr

.global add_asm
.type add_asm, %function
add_asm:
    add r0, r0, r1
    bx lr

