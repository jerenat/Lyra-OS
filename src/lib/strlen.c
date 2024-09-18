int strlen(const char *text) {
    const char *inicio = text;  // Guardar el inicio del puntero

    while (*text) {
        text++;  // Mover el puntero al siguiente carácter
    }

    return text - inicio;  // Calcular la longitud como la diferencia de punteros
}
