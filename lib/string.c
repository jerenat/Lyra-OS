/*
    This file is part of Luxur
    Copyright (C) 2010 - 2013 Esteban Misael Maltauro

    Luxur is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Luxur is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
