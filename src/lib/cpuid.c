#include <stdio.h>

// Función para ejecutar la instrucción cpuid
void _cpuid(int code, uint32_t *a, uint32_t *d)
{
    asm volatile("cpuid"
                 : "=a"(*a), "=d"(*d)
                 : "a"(code)
                 : "ecx", "ebx");
}

void arch()
{
    uint32_t eax, edx;

    // Obtener información del procesador
    _cpuid(1, &eax, &edx);

    // Verificar el bit 29 de edx
    if (edx & (1 << 29))
    {
        printf("\nArquitectura: x86_64 (64 bits)\n");
    }
    else
    {
        printf("\nArquitectura: x86 (32 bits)\n");
    }
}