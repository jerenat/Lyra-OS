#include <stddef.h>

void strcat(char *dest, const char *org)
{
    // Verificar punteros nulos
    if (dest == NULL || org == NULL) {
        return;
    }

    // Buscar el final de dest
    while (*dest) {
        dest++;
    }

    // Copiar org al final de dest
    while ((*dest++ = *org++)) {
        // Nada más que hacer aquí, el ciclo se ejecuta hasta encontrar el '\0' de org
    }
}
