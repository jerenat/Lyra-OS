/*
Archivo Creado Por Sebastian Fernandez Fue adaptado 
a luxur Por Esteban Maltauro con el permiso del autor.
*/

#include <stdio.h>

void *memcpy(void *dest,const void *source,unsigned long length)
{
	unsigned int d0;
	__asm__ __volatile__("rep  movsl"
		: "=S"(source), "=D"(d0)
		: "S"(source), "D"(dest), "c"(length>>2)
	);
	__asm__ __volatile__("rep movsb"
		:
		: "S"(source), "D"(d0), "c"(length&0x03)
	);
	return dest;
}

void *memset(void *dest, unsigned char value,unsigned long length)
{
	unsigned int d0;
	__asm__ __volatile__("rep  stosb"
		: "=D"(d0)
		: "a"(value), "D"(dest), "c"(length)
	);
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short value,unsigned long length)
{
	unsigned int d0;
	__asm__ __volatile__("rep  stosw"
		: "=D"(d0)
		: "a"(value), "D"(dest), "c"(length)
	);
}

unsigned long *memsetl(unsigned long *dest, unsigned int value,unsigned long length)
{
	unsigned int d0;
	__asm__ __volatile__("rep  stosl"
		: "=D"(d0)
		: "a"(value), "D"(dest), "c"(length)
	);
}
