//Libreria basica del kernel. definicion de las funciones mas usadas de la lib C//

#include <stddef.h>

// -- Variables globales



// -- COLORES
#define rgb(r,g,b)			((r << 16) + (g << 8) + b)

// Paleta de colores RGB
#define BLACK				rgb(0,0,0)
#define RED				rgb(222,56,43)
#define GREEN				rgb(57,181,74)
#define YELLOW				rgb(255,199,6)
#define BLUE				rgb(0,111,184)
#define MAGENTA				rgb(118,38,113)
#define CYAN				rgb(44,181,233)
#define GRAY				rgb(170,170,170)
#define DARK_GRAY			rgb(128,128,128)
#define BRIGHT_RED			rgb(255,0,0)
#define BRIGHT_GREEN			rgb(0,255,0)
#define BRIGHT_YELLOW			rgb(255,255,0)
#define BRIGHT_BLUE			rgb(0,0,255)
#define BRIGHT_MAGENTA			rgb(255,0,255)
#define BRIGHT_CYAN			rgb(0,255,255)
#define WHITE				rgb(255,255,255)
// -- END COLORES




int printf(char * buf, ...);		// imprime en pantalla texto
void strcat(char *dest, const char *org);
void cls();	// limpiar pantalla
int strlen(const char *text); 
int strcmp(const char *s,const char *t);	// compara carácterres
int strcpy(char *dest,const char *org);		// copiar string
int putchar(char ch);
void *memcpy(void *dest,const void *source,unsigned long length);
void *memset(void *dest, unsigned char value,unsigned long length);
unsigned short *memsetw(unsigned short *dest, unsigned short value,unsigned long length);
unsigned long *memsetl(unsigned long *dest, unsigned int value,unsigned long length);
void sleep(int ms);		// espera x tiempo en ms (ej: 1s => 1000ms)
int kprintf(int linia,int columna,char *text,char *color);		// imprime texto del kernel
int puts(char *c);		// -- similar a printf
int atoi(char* palabra); 
char* gets();		// obtiene los carácteres del teclado, similar a "scanf"
unsigned char getch();
void exec(unsigned int addr);
void reboot();
void execute_program(char *path);	// -- ejecutar programas
void execute_file(char *path);		// -- abrir archivos
void shell();



#define cli() __asm__("cli")
#define sti() __asm__("sti")

//si hay un panic detenemos el kernel luego de mostrar el Error.
#define panic(msg) ({\
	 asm volatile("cli");\
	printf(msg); \
	for(;;); \
	})

#define ASSERT(msg) ({\
	 asm volatile("cli");\
	printf(msg); \
	for(;;); \
	})

