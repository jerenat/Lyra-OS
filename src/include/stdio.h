//Libreria basica del kernel. definicion de las funciones mas usadas de la lib C//

#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// -- Variables globales

int printf(char * buf, ...);		// imprime en pantalla texto
void strcat(char *dest, const char *org);
void cls();	// limpiar pantalla
int putchar(char ch);
//int kputchar(char ch, unsigned char color);
void *memcpy(void *dest,const void *source,unsigned long length);
void *memset(void *dest, unsigned char value,unsigned long length);
unsigned short *memsetw(unsigned short *dest, unsigned short value,unsigned long length);
unsigned long *memsetl(unsigned long *dest, unsigned int value,unsigned long length);
void sleep(int ms);		// espera x tiempo en ms (ej: 1s => 1000ms)
//int kprintf(unsigned char color, char *buf, ...);		// imprime texto del kernel
int puts(char *c);		// -- similar a printf
int atoi(char* palabra); 
char* gets();		// obtiene los carácteres del teclado, similar a "scanf"
unsigned char getch();
void exec(unsigned int addr);
void reboot();
void power_off();
void execute_program(char *path);	// -- ejecutar programas
void execute_file(char *path);		// -- abrir archivos
void shell();
int isdigit(int c);			// -- define si el número es un dígito
void _cpuid(int code, uint32_t *a, uint32_t *d);
void arch();
char* read_file_to_string(const char *path);
char *fgets(const char *filename);



#define cli() __asm__("cli")
#define sti() __asm__("sti")

//si hay un panic detenemos el kernel luego de mostrar el Error.
#define panic(msg) ({\
	__asm__ volatile("cli");\
	printf(msg); \
	for(;;); \
	})

#define ASSERT(msg) ({\
	__asm__ volatile("cli");\
	printf(msg); \
	for(;;); \
	})

