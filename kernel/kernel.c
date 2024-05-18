#include <boot/multiboot.h>
#include <es.h>
#include <paging.h>
#include <kheap.h>
#include <descriptor_tables.h>
#include <timer.h>
#include <floppy/floppy.h>
#include <fat12.h>
#include <dma.h>
#include <syscall.h>
#include <keyboard.h>
#include <stdio.h>
#include <../kernel/ia32.c>

void shell(); //prototipo de la shell
unsigned int initial_esp;

void main(unsigned int initial_stack)
{
  
  initial_esp = initial_stack;

    iniciar_descriptor_table();
    printf("Descriptor Table.................[ok]\n\n");

    init_keyboard();
    printf("Teclado..........................[ok]\n\n");

    init_timer(100);
    printf("Timer Frecuencia (100)...........[ok]\n\n");

    sti();
    printf("Iniciando Interrupciones.........[ok]\n\n");

    dma_alloc_init();
    printf("DMA Controler....................[ok]\n\n");

    init_floppy();
    printf("Driver Floppy....................[ok]\n\n");
    

    if(mount_fat12() == 1){
      printf("FAT12............................[ok]\n\n");
    }else{
      panic("Error en Fat!");
    }

    initialise_syscalls();
    printf("Iniciando Syscall................[ok]\n\n\n");

      
puts("Presione Enter Para habilitar el teclado: ");
char *habilitar_teclado;
habilitar_teclado = gets();



printf("Bienvenido!!");


printf("Escriba help para obtener ayuda..\n");
printf(" \n");

shell();


}


