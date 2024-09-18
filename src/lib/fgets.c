#include <stdio.h>

// -- Extrae el texto de un archivo, y lo retorna para ser usado por una variable tipo char
char *fgets(const char *filename)
{
    char *file_content = read_file_to_string(filename);

    if (file_content)
    {
        return file_content;
    }
    else
    {
        return NULL;
    }
}