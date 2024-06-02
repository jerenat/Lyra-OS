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
#include <time/rand.h>

unsigned int initial_esp;


// -- inicia los complementos del Kernel
void start_complements(){

    iniciar_descriptor_table();
    printf("Starting descriptor table\n\n");

    init_keyboard();
    printf("Starting keyboard\n\n");

    init_timer(100);
    printf("Starting timer frecuency in 100ms\n\n");

    sti();
    printf("Starting interruptions\n\n");

    dma_alloc_init();
    printf("Starting dma controller\n\n");

    init_floppy();
    printf("Starting floppy driver\n\n");
    

    if(mount_fat12() == 1){
      printf("Starting FS Fat12\n\n");
    }else{
      panic("FAT Error!");
    }

    initialise_syscalls();
    printf("Starting system calls\n\n\n");
}

// -- Iniciar teclado y carácteres
void start_keyboard(){
  puts("Presione [Enter] Para habilitar el teclado: ");
  
  char *habilitar_teclado;
  habilitar_teclado = gets();
}



void main(unsigned int initial_stack)
{
  
  initial_esp = initial_stack;


  start_complements();
  
  start_keyboard();


  int size = rand();
  printf("valor: %u", size);

  shell();
}


