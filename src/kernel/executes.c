#include <stdio.h>  // Biblioteca estándar de entrada y salida
#include <fat12.h>  // Funciones para trabajar con el sistema de archivos FAT12


// -- Ejecutar programa (esencial para abrir archivos por defecto)
void execute_program(char *path) {
    // Obtener el tamaño del archivo especificado por la ruta 'path'
    int filesize = get_file_size(path);

    // Definir un buffer estático de 70,000 bytes para almacenar el contenido del archivo
    static char buff[70000];
    
    // Abrir el archivo y leer su contenido en el buffer 'buff'
    file_open(path, buff);

    // Asignar 70,000 bytes de memoria dinámica (heap) para el programa
    unsigned int moduleptr = kmalloc(70000);

    // Copiar el contenido del buffer 'buff' a la dirección de memoria reservada en 'moduleptr'
    memcpy((void *)moduleptr, (void *)buff, filesize);

    // Ejecutar el contenido del archivo cargado en 'moduleptr'
    exec(moduleptr);
}

// -- Leer el contenido de un archivo y retornarlo como una cadena (string)
char* read_file_to_string(const char *path) {
    int rec = 0;  // Variable para llevar el registro de la posición en el archivo
    static char buff[70000];  // Buffer estático para almacenar el contenido del archivo

    // Abrir el archivo y leer su contenido en el buffer 'buff'
    file_open(path, buff);

    // Obtener la longitud del contenido almacenado en 'buff'
    unsigned int length = strlen(buff);

    // Asignar memoria dinámica suficiente para almacenar el contenido del archivo más un carácter nulo
    char *file_content = (char *)kmalloc((length + 1) * sizeof(char));
    if (!file_content) {  // Verificar si la asignación de memoria fue exitosa
        printf("No se pudo asignar memoria");
        return NULL;  // Si no se pudo asignar memoria, retorna NULL
    }

    // Copiar el contenido del buffer 'buff' al área de memoria 'file_content'
    while (buff[rec] != '\0') {
        file_content[rec] = buff[rec];
        rec++;
    }
    // Añadir el carácter nulo ('\0') al final de 'file_content' para finalizar la cadena
    file_content[rec] = '\0';

    // Devolver el contenido del archivo como una cadena
    return file_content;
}

// -- Abrir archivos y mostrar su contenido en la consola
void execute_file(char *path) {
    int rec = 0;  // Variable para llevar el registro de la posición en el archivo
    static char buff[70000];  // Buffer estático para almacenar el contenido del archivo

    // Abrir el archivo y leer su contenido en el buffer 'buff'
    file_open(path, buff);

    // Recorrer el contenido del buffer y mostrar cada carácter en la consola usando 'putchar'
    while (buff[rec] != '\0') {
        putchar(buff[rec]);  // Mostrar el carácter en la consola
        rec++;
    }
}
