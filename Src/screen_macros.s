.macro fill_8_bits screen_buff, bits, set_color, res_color, temp_res
    mov \temp_res, \set_color
    tst \bits, #0x80
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0000]

    mov \temp_res, \set_color
    tst \bits, #0x40
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0180]

    mov \temp_res, \set_color
    tst \bits, #0x20
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0300]

    mov \temp_res, \set_color
    tst \bits, #0x10
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0480]

    mov \temp_res, \set_color
    tst \bits, #0x08
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0600]

    mov \temp_res, \set_color
    tst \bits, #0x04
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0780]

    mov \temp_res, \set_color
    tst \bits, #0x02
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0900]

    mov \temp_res, \set_color
    tst \bits, #0x01
    it eq
    moveq \temp_res, \res_color
    strh \temp_res, [\screen_buff, #0x0a80]
.endm

.macro get_attr_color r_set_color, r_res_color, r_attr_addr, n_attr_offset, r_color_table
    ldrb \r_set_color, [\r_attr_addr, #\n_attr_offset]
    mov \r_res_color, \r_set_color, ror #0x04
    and \r_set_color, \r_set_color, #0x0f
    and \r_res_color, \r_res_color, #0x0f
    ldrh \r_res_color, [\r_color_table, \r_res_color, lsl #1]
    ldrh \r_set_color, [\r_color_table, \r_set_color, lsl #1]
.endm
