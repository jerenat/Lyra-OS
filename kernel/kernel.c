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

    cls(); // -- limpiar pantalla
    printf("\nIniciando kernel\n\n");

    iniciar_descriptor_table();
    printf("Iniciando tabla de descriptores\n\n");

    // espera x segundos
    sleep_seconds(2);

    init_keyboard();
    printf("Iniciando teclado\n\n");
    sleep_seconds(2);

    init_timer(100);
    printf("Iniciando tiempo de reloj\n\n");
    sleep_seconds(2);

    sti();
    printf("Iniciando interrupciones\n\n");
    sleep_seconds(2);

    dma_alloc_init();
    printf("Iniciando controlador DMA\n\n");

    init_floppy();
    printf("Iniciando Driver FAT12\n\n");
    

    if(mount_fat12() == 1){
      printf("Starting FS Fat12\n\n");
    }else{
      panic("FAT Error!");
    }

    initialise_syscalls();
    printf("Iniciando system calls\n\n\n");
    sleep_seconds(2);
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
  printf("valor: %u\n", size);

  execute_file("logo.txt");

  const char *path = fgets("ejemplo.txt");

  printf("\nTexto obtenido: %s\n", path);
  
  shell();
}


