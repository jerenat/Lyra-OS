#include <stdio.h>
#include <fat12.h>





// -- ejecutar programa (esencial para abrir por defecto)
void execute_program(char *path)
{

    int filesize = get_file_size(path);

    static char buff[70000];
    file_open(path, buff);

    unsigned int moduleptr = kmalloc(70000);

    memcpy((void *)moduleptr, (void *)buff, filesize);

    exec(moduleptr);
}


// -- lee el contenido de un archivo y lo retorna
char* read_file_to_string(const char *path) {
    int rec = 0;
    static char buff[70000];

    // Abrir el archivo y leer su contenido en buff
    file_open(path, buff);

    // Obtener la longitud del contenido del archivo
    unsigned int length = strlen(buff);

    // Asignar memoria para el contenido del archivo usando kmalloc
    char *file_content = (char *)kmalloc((length + 1) * sizeof(char));
    if (!file_content) {
        printf("No se pudo asignar memoria");
        return NULL;
    }

    // Almacenar el contenido del archivo en la variable file_content
    while (buff[rec] != '\0') {
        file_content[rec] = buff[rec];
        rec++;
    }
    // Añadir el carácter nulo al final de file_content
    file_content[rec] = '\0';

    return file_content;
}


// -- abrir archivos
void execute_file(char *path)
{

    int rec = 0;
    static char buff[70000];

    file_open(path, buff);

    while (buff[rec] != '\0')
    {
        putchar(buff[rec]);
        rec++;
    }
}

