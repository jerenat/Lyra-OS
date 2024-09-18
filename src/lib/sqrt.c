// sqrt.c

#include <stdio.h>

// Definición de la tabla y macros
#define ITABLE_SIZE 16
#define ITABLE_ELEMENT_SIZE sizeof(double)
static double itable[ITABLE_SIZE] = {
    0x1.6a09e667f3bccp+0, 0x1.5bf0a8b145769p+0, 0x1.8b8p+0, 0x1.62e42fefa39efp+0,
    0x1.eaad67e8a3d3cp-1, 0x1.6a09e667f3bccp+0, 0x1.5bf0a8b145769p+0, 0x1.8b8p+0,
    0x1.62e42fefa39efp+0, 0x1.eaad67e8a3d3cp-1, 0x1.6a09e667f3bccp+0, 0x1.5bf0a8b145769p+0,
    0x1.8b8p+0, 0x1.62e42fefa39efp+0, 0x1.eaad67e8a3d3cp-1, 0x1.6a09e667f3bccp+0
};



// Función para normalizar y calcular el exponente
static int norm2(double *t)
{
    unsigned e, f, g;

    f = (((unsigned *) t)[1]) >> 1;
    e = ((unsigned *) t)[1];
    f += 0x1FF80000;
    g = (e & 0x000FFFFF);
    f &= 0xFFF00000;
    ((int *) t)[1] = g + 0x40000000 - (e & 0x00100000);

    return f;
}



// Función para calcular la raíz cuadrada
double sqrt(double y)
{
    double a;
    int e, c;

    // Normaliza y calcula el exponente
    e = norm2(&y);

    // Determina el índice en la tabla según el patrón de bits del número
    c = (((int *) &y)[1] >> 18) & 7;

    // Obtiene un valor inicial de la tabla
    a = itable[c];

    // Itera para aproximar la raíz cuadrada usando el método de Newton-Raphson
    for (int i = 0; i < 6; i++) {
        a = 0.5 * a * (3.0 - y * a * a);
    }

    a *= y;  // Multiplica por y para obtener la raíz cuadrada aproximada

    // Ajusta el resultado final
    ((int *) &a)[1] &= 0x000FFFFF;
    ((int *) &a)[1] |= e;

    return a; // Retorna el resultado de la raíz cuadrada aproximada
}