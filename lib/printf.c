#include <stdarg.h>
#include <stdio.h>

#define ITOA 		0x01
#define LOWER_CASE 	0x02
#define UPPER_CASE 	0x04

#define VIDEO_TEXT 0xB8000


unsigned short *video_txt=(unsigned short *)VIDEO_TEXT;

// Implementación de memsetw para llenar la memoria con un valor específico
void _memsetw(unsigned short *dest, unsigned short val, size_t count) {
    for (size_t i = 0; i < count; i++) {
        dest[i] = val;
    }
}



int printf(char *buf, ...) {
    char ch;
    int lflags = 0;
    int i = 0;
    int number_arg;
    unsigned int unsigned_arg;
    int32_t int32_arg;
    char *string;
    char number[20];
    unsigned long len;
    va_list args;

    va_start(args, buf);

    for (;;) {
        while ((ch = *buf++) != '%') {
            if (ch == '\0') {
                va_end(args);
                return 0;
            }
            putchar(ch);
        }
        switch (*buf++) {
        case '%': putchar('%'); break;
        case '-': putchar(' '); break;
        case 'c': putchar(va_arg(args, int)); break;
        case 's':
            string = va_arg(args, char *);
            while (*string != '\0')
                putchar(*string++);
            break;
        case 'i':
        case 'd':
            number_arg = va_arg(args, int);
            if (number_arg == 0) {
                putchar('0');
                break;
            }
            if (number_arg < 0) {
                putchar('-');
                number_arg = -number_arg;
            }
            i = 19;
            for (i = 19; number_arg != 0; i--, number_arg /= 10)
                number[i] = (number_arg % 10) + '0';
            i++;
            while (i < 20)
                putchar(number[i++]);
            break;
        case 'u':
            unsigned_arg = va_arg(args, unsigned int);
            if (unsigned_arg == 0) {
                putchar('0');
                break;
            }
            i = 19;
            for (i = 19; unsigned_arg != 0; i--, unsigned_arg /= 10)
                number[i] = (unsigned_arg % 10) + '0';
            i++;
            while (i < 20)
                putchar(number[i++]);
            break;
        case 'z':
            if (*buf == 'u') {
                buf++;
                unsigned_arg = va_arg(args, size_t);
                if (unsigned_arg == 0) {
                    putchar('0');
                    break;
                }
                i = 19;
                for (i = 19; unsigned_arg != 0; i--, unsigned_arg /= 10)
                    number[i] = (unsigned_arg % 10) + '0';
                i++;
                while (i < 20)
                    putchar(number[i++]);
            }
            break;
        case 'x':
            lflags |= ITOA;
            lflags |= LOWER_CASE;
            break;
        case 'X':
            lflags |= ITOA;
            lflags |= UPPER_CASE;
            break;
        case 'p':
            putchar('[');
            number_arg = va_arg(args, unsigned long);
            for (i = 7; i >= 0; i--, number_arg >>= 0x04) {
                if ((number_arg & 0x0F) > 9)
                    number[i] = (number_arg & 0x0F) + 'A' - 10;
                else
                    number[i] = (number_arg & 0x0F) + '0';
            }
            i++;
            while (i != 8) {
                if (i == 4)
                    putchar(':');
                putchar(number[i++]);
            }
            putchar(']');
            break;
        case 't':
            if (*buf == 'd') {
                buf++;
                int32_arg = va_arg(args, int32_t);
                if (int32_arg == 0) {
                    putchar('0');
                    break;
                }
                if (int32_arg < 0) {
                    putchar('-');
                    int32_arg = -int32_arg;
                }
                i = 19;
                for (i = 19; int32_arg != 0; i--, int32_arg /= 10)
                    number[i] = (int32_arg % 10) + '0';
                i++;
                while (i < 20)
                    putchar(number[i++]);
            }
            break;
        default:
            break;
        }
        if (lflags & ITOA) {
            number_arg = va_arg(args, unsigned long);
            if (number_arg == 0) {
                putchar('0');
            } else {
                for (i = 7; number_arg != 0;
                     i--, number_arg = (number_arg >> 4) & 0x0FFFFFFF) {
                    if ((number_arg & 0x0F) > 9) {
                        if (lflags & LOWER_CASE)
                            number[i] = (number_arg & 0x0F) + 'a' - 10;
                        else
                            number[i] = (number_arg & 0x0F) + 'A' - 10;
                    } else
                        number[i] = (number_arg & 0x0F) + '0';
                }
                i++;
                while (i < 8)
                    putchar(number[i++]);
            }
            lflags = 0;
        }
    }
}

int putchar(char ch) {
    static unsigned int crs_y = 0;
    static unsigned int crs_x = 0;
    unsigned short *video_txt;
    unsigned short blank;
    blank = 0x20 | (0x0F << 8); // Espacio en blanco con color de fondo negro y texto blanco
    int c = 0; // Bandera de retroceso

    // Manejo de caracteres especiales
    if (ch == '\n') {
        crs_y++;
        crs_x = 0;
        return 0;
    }
    if (ch == '\t') {
        crs_x += 4;
        return 0;
    }
    if (ch == '\b') {
        if (crs_x > 0) {
            crs_x--;
        }
        ch = ' ';
        c = 1;
    }

    // Salto de línea si llegamos al final de la línea
    if (crs_x == 80) {
        crs_y++;
        crs_x = 0;
    }

    // Desplazamiento de la pantalla si llegamos al final de la pantalla
    if (crs_y >= 25) {
        // Mover el texto una línea hacia arriba
        memcpy((void *)VIDEO_TEXT, (void *)(VIDEO_TEXT + 80 * 2), 24 * 80 * 2);
        // Limpiar la última línea
        _memsetw((void *)(VIDEO_TEXT + 24 * 80 * 2), blank, 80);
        crs_y = 24;
    }

    // Escribir el carácter en la memoria de video
    video_txt = (unsigned short *)(VIDEO_TEXT + (crs_y * 80 + crs_x) * 2);
    *video_txt = ch | (0x7 << 8); // Color de texto blanco sobre fondo negro

    if (!c) { // Incrementar crs_x solo si no es un retroceso
        crs_x++;
    }

    return 0;
}


int puts(char *c){

printf(c);



}
