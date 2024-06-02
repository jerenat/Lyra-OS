#include <syscall.h>
#include <isr.h>
#include <stdio.h> //libC//
#include <fat12.h> //funciones de Archivos//

static void syscall_handler(registros *regs);

static void *syscalls[12] =
{
    &cls, //0
    &puts,    //1
    &gets,    //2
    &file_open,//3
    &sleep,//4
    &shell,//5
    &putchar,//6
    &kprintf,//7
    &exec,//8
    &cd,//9
    &get_file_size,//10
    &ls,//11
};
unsigned int num_syscalls = 12;

void initialise_syscalls()
{
    //Registramos la syscall en la interrupcion 0x80
    register_interrupt_handler (0x80, &syscall_handler);
}

void syscall_handler(registros *regs)
{
    //eax contiene el Numero de la syscall, verificamos que el numero corresponda a alguna syscall//
    if (regs->eax >= num_syscalls)
        return;

    // tomamos la localizacion de la syscall en la tabla, es un puntero a la funcion
    void *location = syscalls[regs->eax];

    //metemos los parametros en la pila
    //llamamos a la funcion
    //retornamos en eax..lo que devolvio la funcion
    int ret;
    asm volatile (" \
      push %1; \
      push %2; \
      push %3; \
      push %4; \
      push %5; \
      call *%6; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
    " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
    regs->eax = ret;
}
