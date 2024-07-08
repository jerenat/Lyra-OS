#include <stdio.h>

int strncmp(const char *s1, const char *s2, size_t length)
{
    // La función strncmp compara los primeros (como máximo) length caracteres de s1 y s2.
    // Devuelve un entero menor, igual o mayor que cero si s1 se encuentra, respectivamente,
    // menor que, igual a o mayor que s2.

    // Si length es 0, las cadenas son consideradas iguales.
    if (length == 0)
    {
        return 0;
    }

    for (size_t i = 0; i < length; i++)
    {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
        {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
    }

    // Si llegamos aquí, las cadenas son iguales hasta length caracteres.
    return 0;
}
