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