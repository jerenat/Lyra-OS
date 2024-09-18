#include <stddef.h> // Para tipos de datos estándar como uint16_t

#define VIDEO_MEMORY_START 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define CHAR_BYTES 2 // Cada carácter en modo texto ocupa 2 bytes (uno para el carácter y otro para el atributo)

void cls()                                  
{
    uint16_t *video_memory = (uint16_t*)VIDEO_MEMORY_START;
    int i;

    for (i = 0; i < SCREEN_SIZE; i++) {
        video_memory[i] = 0x0000; // Limpia toda la pantalla con caracteres en color negro
    }
}