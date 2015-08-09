#include "debug_msg.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

void send_command(int command, void *message)
{
   asm("mov r0, %[cmd];"
       "mov r1, %[msg];"
       "bkpt #0xAB"
         :
         : [cmd] "r" (command), [msg] "r" (message)
         : "r0", "r1", "memory");
}

static char buff[0x1000];

void print_num(char *description, int num)
{
    //return;
    sprintf(buff, "%s: %d\n",description, num);
    uint32_t m[] = { 1/*stderr*/, (uint32_t)buff, strlen(buff) };
    send_command(0x05/* some interrupt ID */, m);
}
