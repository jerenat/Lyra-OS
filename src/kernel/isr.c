#include <isr.h>  // Cabecera para gestionar las rutinas de servicio de interrupciones (ISR)
#include <es.h>   // Definiciones del sistema (entrada/salida y otras funciones)
#include <stdio.h> // Biblioteca estándar de entrada y salida

// Array de manejadores de interrupciones (handlers) con un máximo de 256 entradas (una por cada interrupción posible)
registros_isr interrupt_handlers[256];

// -- Registra un manejador de interrupción en una posición específica del array
void register_interrupt_handler(unsigned char n, registros_isr handler)
{
    // Asigna el manejador de interrupción (handler) al número de interrupción 'n'
    interrupt_handlers[n] = handler;
}

// -- Manejador genérico para las interrupciones del sistema (ISR)
void isr_handler(registros regs)
{
    // Obtener el número de la interrupción
    unsigned char int_no = regs.int_no & 0xFF;

    // Si hay un manejador registrado para esta interrupción
    if (interrupt_handlers[regs.int_no] != 0)
    {
        // Recuperar el manejador de interrupciones registrado y ejecutarlo
        registros_isr handler = interrupt_handlers[regs.int_no];
        handler(&regs);
    }
    else
    {
        // Si no hay manejador para esta interrupción, se notifica con un mensaje
        printf("Unhandled interrupt: %d\n", regs.int_no);
        
        // Bucle infinito que detiene el kernel al no manejar la interrupción
        for(;;);
    }
}

// -- Manejador para interrupciones IRQ (interrupciones de hardware)
void irq_handler(registros regs)
{
    // Si el número de interrupción es mayor o igual a 40, se está tratando con el PIC esclavo
    if (regs.int_no >= 40)
    {
        // Enviar señal de "end of interrupt" (EOI) al PIC esclavo (0xA0)
        outb(0xA0, 0x20);
    }
    
    // Enviar señal EOI al PIC maestro (0x20)
    outb(0x20, 0x20);

    // Si hay un manejador registrado para la interrupción actual, se ejecuta
    if (interrupt_handlers[regs.int_no] != 0)
    {
        // Recuperar el manejador de interrupción registrado y ejecutarlo
        registros_isr handler = interrupt_handlers[regs.int_no];
        handler(&regs);
    }
}
