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
#include <stdio.h>  // librería del kernel
#include <colors.h> // libreria de colores

void shell(); // prototipo de la shell
unsigned int initial_esp;

// -- Inicializar formato de particionado
void start_fat()
{

  if (mount_fat12() == 1)
  {
    printf("Starting partition");
  }
  else
  {
    panic("Error to mount partition");
  }
}

void start_services()
{

  // -- Estructura de datos utilizada para organizar información importante relacionada
  // con la operación del sistema, como segmentos de memoria
  // y rutinas de manejo de interrupciones.
  iniciar_descriptor_table();
  printf("Starting descriptor table");

  // -- Iniciar teclado
  init_keyboard();
  printf("Starting keyboard\n\n");

  //
  init_timer();
  printf("Starting timer in \n\n");

  sti();
  printf("Start interruptions\n\n");

  dma_alloc_init();
  printf("Dynamic access memory\n\n");

  init_floppy();
  printf("Driver Floppy....................[ok]\n\n");

  // -- Iniciar partición
  start_fat();

  // -- Inicializando llamadas al sistema
  initialise_syscalls();
  printf("Syscall starting\n\n\n");
}

void main(unsigned int initial_stack)
{

  initial_esp = initial_stack;

  start_services();

  puts("Presione Enter Para habilitar el teclado: ");
  char *habilitar_teclado;
  habilitar_teclado = gets();
  cls(); // teclado habilitado, borramos la pantalla eh iniciamos la shell

  printf("                   #       #    #   #     #  #    #  ######\n");
  printf("                   #       #    #    #   #   #    #  #   #\n");
  printf("                   #       #    #     # #    #    #  #  #\n");
  printf("                   #       #    #     # #    #    #  ####\n");
  printf("                   #       #    #    #   #   #    #  #   #\n");
  printf("                   ######  ######   #     #  ######  #    #\n");
  printf("                  Copyright (C) 2010 - 2013 Esteban Misael Maltauro\n");
  printf("              Luxur is free software: GNU General Public License\n");
  printf(" \n");
  printf("Escriba help para obtener ayuda..\n");
  printf(" \n");

  shell(); // pasamos a la shell una vez iniciado todo Correctamente
}
