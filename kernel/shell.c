#include <stdio.h>     // Biblioteca estándar de entrada y salida
#include <fat12.h>     // Incluye funciones del sistema de archivos FAT12
#include "ia32.c"      // Arquitectura x86 IA-32
#include <version.h>   // Definiciones de versión del sistema

#define MAX_COMMAND_LENGTH 200   // Tamaño máximo del comando
#define MAX_ARGUMENT_LENGTH 200  // Tamaño máximo del argumento
#define MAX_BUFFER_SIZE 70000    // Tamaño máximo del buffer para archivos

/**
 * Muestra los comandos disponibles de la consola.
 */
void help() {
    printf("\n===================== Shell =========================\n");
    printf("Comandos disponibles:\n");
    printf("ls             - Lista el directorio actual\n");
    printf("cd [dir]       - Cambia de directorio (ej: cd ..)\n");
    printf("exec [file]    - Ejecuta un archivo (ej: exec hola.exe)\n");
    printf("vi [file]      - Muestra el contenido de un archivo (ej: vi license.txt)\n");
    printf("help           - Muestra esta ayuda\n");
    printf("reboot         - Reinicia el sistema\n");
    printf("cls            - Limpia la pantalla\n");
    printf("echo [message] - Muestra un mensaje en pantalla\n");
    printf("version        - Muestra la versión del sistema\n");
    printf("pwd            - Muestra la ruta actual\n");
    printf("arch           - Muestra la arquitectura del sistema\n");
    printf("\n======================================================\n");
}

/**
 * Cambia el directorio actual a `path`.
 */
void shell_cd(char *path) {
    cd(path);  // Función que cambia el directorio a la ruta especificada
}

/**
 * Ejecuta un programa desde el archivo `path`.
 */
void shell_exec(char *path) {
    int filesize = get_file_size(path);        // Obtiene el tamaño del archivo
    static char buff[MAX_BUFFER_SIZE];         // Buffer estático para el archivo
    file_open(path, buff);                     // Abre el archivo y lo carga en `buff`
    unsigned int moduleptr = kmalloc(MAX_BUFFER_SIZE);  // Reserva memoria
    memcpy((void*)moduleptr, (void*)buff, filesize);    // Copia el archivo a la memoria reservada
    exec(moduleptr);                            // Ejecuta el programa desde la memoria
}

/**
 * Muestra el contenido de un archivo en la consola.
 */
void shell_vi(char *path) {
    int rec = 0;
    static char buff[MAX_BUFFER_SIZE];
    file_open(path, buff);  // Abre el archivo y lo carga en `buff`
    
    // Muestra el contenido del archivo
    while(buff[rec] != '\0') {
        putchar(buff[rec]);  // Imprime carácter por carácter
        rec++;
    }
}

/**
 * Bucle principal de la consola (shell) que interpreta y ejecuta comandos.
 */
void shell() {
    static char *comand;   // Comando ingresado por el usuario
    static char cmd[MAX_COMMAND_LENGTH];  // Parte del comando
    static char argv[MAX_ARGUMENT_LENGTH]; // Argumento del comando
    int argc = 0;  // Cantidad de argumentos
    int bb = 0;    // Índice para el buffer
    static int c;

    // Bucle infinito para ejecutar la consola
    for(;;) {
        printf("\nuser$:");  // Muestra el prompt
        comand = gets();     // Captura la entrada del usuario

        // Separa el comando de los argumentos
        while((c = *comand++) != ' ' && c != 0) {
            cmd[bb] = (unsigned char)c;
            bb++;
        }

        // Final del comando
        cmd[bb] = '\0';
        bb = 0;

        // Si no es el final, hay argumentos
        argc = (c != 0) ? 1 : 0;

        // Obtener los argumentos (si los hay)
        while((c = *comand++) != 0) {
            argv[bb] = (unsigned char)c;
            bb++;
        }

        // Final del argumento
        argv[bb] = '\0';
        bb = 0;

        // Procesa el comando ingresado por el usuario
        if(strcmp(cmd, "ls") == 0) {
            printf(" \n");
            ls();  // Lista el contenido del directorio actual
            printf(" \n");
        } else if(strcmp(cmd, "cd") == 0) {
            if(argc != 0) shell_cd(argv);  // Cambia de directorio
            else printf("No hay Argumentos\n");
        } else if(strcmp(cmd, "exec") == 0) {
            if(argc != 0) shell_exec(argv);  // Ejecuta un archivo
            else printf("No hay Argumentos\n");
        } else if(strcmp(cmd, "help") == 0) {
            help();  // Muestra la ayuda
        } else if(strcmp(cmd, "vi") == 0) {
            if(argc != 0) shell_vi(argv);  // Muestra el contenido del archivo
            else printf("No hay Argumentos\n");
        } else if(strcmp(cmd, "reboot") == 0) {
            printf("Rebooting....\n\n");
            sleep_seconds(4);  // Espera 4 segundos
            reboot();  // Reinicia el sistema
        } else if(strcmp(cmd, "cls") == 0) {
            cls();  // Limpia la pantalla
        } else if(strcmp(cmd, "echo") == 0) {
            if(argc != 0) {
                printf("\n%s", argv);  // Imprime el mensaje del usuario
            }
        } else if(strcmp(cmd, "version") == 0) {
            printf("\n%s", VERSION);  // Muestra la versión del sistema
            printf("\n%s", COPYRIGHT); // Muestra el copyright
        } else if(strcmp(cmd, "pwd") == 0) {
            printf("%s", pwd());  // Muestra el directorio actual
        } else if(strcmp(cmd, "arch") == 0) {
            arch();  // Muestra la arquitectura del sistema
        } else {
            printf("Comando no reconocido: %s\n", cmd);  // Comando no reconocido
        }
    }
}
