#include <stdio.h>

/*
La función strrchr busca la última ocurrencia de un carácter específico en una cadena
y devuelve un puntero a esa posición dentro de la cadena.
*/

char *strrchr(const char *string, int character)
{
    // Verificar si el puntero string es nulo
    if (!string)
        return NULL;

    // Definir un puntero que apunte al final de la cadena
    const char *strptr = string + strlen(string);

    // Recorrer la cadena de atrás hacia adelante
    while (strptr >= string)
    {
        if (*strptr == (char)character)
            return (char *)strptr;
        strptr--;
    }

    // Retornar NULL si no se encuentra el carácter
    return NULL;
}
