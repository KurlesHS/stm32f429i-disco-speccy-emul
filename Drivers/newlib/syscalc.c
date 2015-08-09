#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

extern uint32_t __get_MSP(void);

/*
 write - запись в файл - у нас есть только stderr/stdout
 */
int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return -1;
}

caddr_t _sbrk(int incr)
{
    extern char _ebss;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;


//    char * stack = (char*) __get_MSP();
    char * stack;
    __asm volatile ("MRS %0, msp\n" : "=r" (stack) );

    if (heap_end + incr > stack)
    {
        _write(STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}
