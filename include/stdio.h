
//Libreria basica del kernel. definicion de las funciones mas usadas de la lib C//
int printf(char * buf, ...);
void strcat(char *dest, const char *org);
void cls();
int strlen(const char *text);
int strcmp(const char *s,const char *t);
int strcpy(char *dest,const char *org);
int putchar(char ch);
void *memcpy(void *dest,const void *source,unsigned long length);
void *memset(void *dest, unsigned char value,unsigned long length);
unsigned short *memsetw(unsigned short *dest, unsigned short value,unsigned long length);
unsigned long *memsetl(unsigned long *dest, unsigned int value,unsigned long length);
void sleep(int ms);
int kprintf(int linia,int columna,char *text,char *color);
int puts(char *c);
int atoi(char* palabra); 
char* gets();
unsigned char getch();
void exec(unsigned int addr);
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

