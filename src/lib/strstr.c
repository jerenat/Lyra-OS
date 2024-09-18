#include <stdio.h>

char *strstr(const char *s1, const char *s2) {
    // Si s2 es una cadena vacía, devuelve s1
    if (!*s2) {
        return (char *)s1;
    }

    int s2Len = strlen(s2);

    // Recorre s1
    while (*s1) {
        // Compara las primeras s2Len caracteres de s1 con s2
        if (!strncmp(s1, s2, s2Len)) {
            return (char *)s1;
        }
        s1++;
    }

    // No se encontró s2 en s1
    return NULL;
}
