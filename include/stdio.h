// Libreria basica del kernel. definicion de las funciones mas usadas de la lib C//
typedef unsigned long size_t;




// -- TEXTO
int printf(char *buf, ...);			// -- Texto en consola
int kprintf(char *text, int color); // -- Texto de kernel

void strcat(char *dest, const char *org);
void cls(); // -- Limpiar pantalla
int strlen(const char *text);
int length(const char arr[]);
int strcmp(const char *s, const char *t);	// -- comparar textos
int strcpy(char *dest, const char *org);
int putchar(char ch);
void *memcpy(void *dest, const void *source, unsigned long length);
void *memset(void *dest, unsigned char value, unsigned long length);
unsigned short *memsetw(unsigned short *dest, unsigned short value, unsigned long length);
unsigned long *memsetl(unsigned long *dest, unsigned int value, unsigned long length);
void sleep(int ms);
int puts(char *c);
int atoi(char *palabra);
char *gets();
unsigned char getch();
void exec(unsigned int addr);
void shell();

#define cli() __asm__("cli")
#define sti() __asm__("sti")

// kernel pannic
#define panic(msg) ({    \
	asm volatile("cli"); \
	cls();               \
	kprintf(msg, 4);     \
	for (;;)             \
		;                \
})

#define ASSERT(msg) ({   \
	asm volatile("cli"); \
	printf(msg);         \
	for (;;)             \
		;                \
})
