#include <stddef.h>

// -- Funciones de entrada y Salida de puertos

// -- Espera el encendido (en ms)
void iowait(void) {
    __asm__ volatile (
        "outb %%al, $0x80\n"
        "outb %%al, $0x80\n"
        :
        : // No input operands
        : "al" // Clobbered registers
    );
}

// -- Salida de puertos e informacion
void outb(uint16_t port, uint8_t data) {
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(data), "Nd"(port)
    );
}

// -- Entrada de puertos e información
uint8_t inb(uint16_t port) {
    uint8_t data;
    __asm__ volatile (
        "inb %1, %0"
        : "=a"(data)
        : "Nd"(port)
    );
    return data;
}