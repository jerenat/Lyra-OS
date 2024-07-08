#include <stdio.h>
#include <fat12.h>
#include "ia32.c"
#include <version.h>

#define MAX_COMMAND_LENGTH 200
#define MAX_ARGUMENT_LENGTH 200
#define MAX_BUFFER_SIZE 70000

/**
 * Comandos de Ayuda de Consola
*/
void help() {
    printf("\n===================== Shell =========================\n");
    printf("Comandos disponibles:\n");
    printf("ls             - Lista el directorio actual\n");
    printf("cd [dir]       - Ingresa o sale de un directorio (ej: cd ..)\n");
    printf("exec [file]    - Ejecuta una aplicacion (ej: exec hola.exe)\n");
    printf("vi [file]      - Muestra el contenido de un archivo (ej: vi license.txt)\n");
    printf("help           - Muestra esta ayuda\n");
    printf("reboot         - Reinicia el sistema\n");
    printf("cls            - Limpia la pantalla\n");
    printf("echo [message] - Muestra un mensaje en pantalla\n");
    printf("version        - Muestra la version del sistema\n");
    printf("pwd            - Muestra la ruta del directorio actual\n");
    printf("arch           - Muestra la arquitectura del sistema\n");
    printf("\n======================================================\n");
}

void shell_cd(char *path) { // cambia de directorio
    cd(path);
}

void shell_exec(char *path) { // ejecuta un archivo
    int filesize = get_file_size(path);
    static char buff[MAX_BUFFER_SIZE];
    file_open(path, buff);
    unsigned int moduleptr = kmalloc(MAX_BUFFER_SIZE);
    memcpy((void*)moduleptr, (void*)buff, filesize);
    exec(moduleptr);
}

void shell_vi(char *path) { // muestra el contenido de un archivo
    int rec = 0;
    static char buff[MAX_BUFFER_SIZE];
    file_open(path, buff);
    while(buff[rec] != '\0') {
        putchar(buff[rec]);
        rec++;
    }
}

void shell() {
    static char *comand;
    static char cmd[MAX_COMMAND_LENGTH];
    static char argv[MAX_ARGUMENT_LENGTH];
    int argc = 0;
    int bb = 0;
    static int c;

    for(;;) {
        printf("\nuser$:"); // pwd devuelve el directorio actual
        comand = gets();

        // Separar el comando del argumento
        while((c = *comand++) != ' ' && c != 0) {
            cmd[bb] = (unsigned char)c;
            bb++;
        }

        // Final del comando
        cmd[bb] = '\0';
        bb = 0;

        // Si es el final del comando es porque no hay argumentos
        argc = (c != 0) ? 1 : 0;

        // Obtener los argumentos
        while((c = *comand++) != 0) {
            argv[bb] = (unsigned char)c;
            bb++;
        }

        // Final del argumento
        argv[bb] = '\0';
        bb = 0;

        // Procesar el comando
        if(strcmp(cmd, "ls") == 0) {
            printf(" \n");
            ls();
            printf(" \n");
        } else if(strcmp(cmd, "cd") == 0) {
            if(argc != 0) shell_cd(argv);
            else printf("No hay Argumentos\n");
        } else if(strcmp(cmd, "exec") == 0) {
            if(argc != 0) shell_exec(argv);
            else printf("No hay Argumentos\n");
        } else if(strcmp(cmd, "help") == 0) {
            help();
        } else if(strcmp(cmd, "vi") == 0) {
            if(argc != 0) shell_vi(argv);
            else printf("No hay Argumentos\n");
        } else if(strcmp(cmd, "reboot") == 0) {
            printf("Rebooting....\n\n");
            sleep_seconds(4);
            reboot();
        } else if(strcmp(cmd, "cls") == 0) {
            cls();
        } else if(strcmp(cmd, "echo") == 0) {
            if(argc != 0) {
                printf("\n%s", argv);
            }
        } else if(strcmp(cmd, "version") == 0) {
            printf("\n%s", VERSION);
            printf("\n%s", COPYRIGHT);
        } else if(strcmp(cmd, "pwd") == 0) {
            printf("%s", pwd());
        } else if(strcmp(cmd, "arch") == 0) {
            arch();
        } else {
            printf("Comando no reconocido: %s\n", cmd);
        }
    }
}


