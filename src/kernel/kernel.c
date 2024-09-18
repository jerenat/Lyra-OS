#include <boot/multiboot.h>         // Incluye definiciones relacionadas con el arranque multiboot
#include <es.h>                     // Definiciones del sistema
#include <paging.h>                 // Gestión de paginación de memoria
#include <kheap.h>                  // Gestión de heap del kernel
#include <descriptor_tables.h>       // Gestión de tablas de descriptores de interrupciones
#include <timer.h>                  // Funciones de temporización
#include <floppy/floppy.h>           // Controlador de disquetes
#include <fat12.h>                  // Funciones para el sistema de archivos FAT12
#include <dma.h>                    // Controlador DMA (Direct Memory Access)
#include <syscall.h>                // Gestión de llamadas al sistema
#include <keyboard.h>               // Funciones del controlador del teclado
#include <stdio.h>                  // Entrada y salida estándar (printf, fgets)
#include <time/rand.h>              // Funciones de generación de números aleatorios

unsigned int initial_esp;           // Variable global para almacenar el puntero de pila inicial

// -- Inicia los complementos del Kernel
void start_complements() {
    cls();  // Limpiar la pantalla
    printf("\nIniciando kernel\n\n");

    iniciar_descriptor_table();  // Iniciar la tabla de descriptores
    printf("Iniciando tabla de descriptores\n\n");

    // Esperar 2 segundos
    sleep_seconds(2);

    init_keyboard();  // Iniciar el controlador del teclado
    printf("Iniciando teclado\n\n");
    sleep_seconds(2);

    init_timer(100);  // Iniciar el temporizador con frecuencia de 100 Hz
    printf("Iniciando tiempo de reloj\n\n");
    sleep_seconds(2);

    sti();  // Habilitar interrupciones
    printf("Iniciando interrupciones\n\n");
    sleep_seconds(2);

    dma_alloc_init();  // Iniciar el controlador DMA
    printf("Iniciando controlador DMA\n\n");

    init_floppy();  // Iniciar el controlador de disquetes
    printf("Iniciando Driver FAT12\n\n");

    // Montar el sistema de archivos FAT12 y verificar si es exitoso
    if (mount_fat12() == 1) {
        printf("Starting FS Fat12\n\n");
    } else {
        panic("FAT Error!");  // Si falla, mostrar mensaje de error
    }

    initialise_syscalls();  // Inicializar las llamadas al sistema
    printf("Iniciando system calls\n\n\n");
    sleep_seconds(2);
}

// -- Iniciar teclado y permitir la entrada de caracteres
void start_keyboard() {
    puts("Presione [Enter] Para habilitar el teclado: ");
  
    char *habilitar_teclado;
    habilitar_teclado = gets();  // Leer entrada del usuario
}

// -- Función principal
void main(unsigned int initial_stack) {
    initial_esp = initial_stack;  // Guardar el puntero de pila inicial

    start_complements();  // Iniciar los complementos del kernel
    start_keyboard();      // Esperar la habilitación del teclado

    // Generar un número aleatorio para el Session ID
    int size = rand();
    printf("\nSession ID: %u\n", size);

    // Ejecutar un archivo llamado "logo.txt"
    execute_file("logo.txt");

    // Leer el contenido de "ejemplo.txt" desde el sistema de archivos
    const char *path = fgets("ejemplo.txt");

    // Mostrar el contenido leído en la consola
    printf("\nTexto obtenido: %s\n", path);
  
    shell();  // Iniciar el shell del sistema
}
