//sslib is part of NuOS Kernel.
//Copyright (C) 2012 Felipe Cabrera

//NuOS kernel is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//NuOS kernel is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

//******************************************************************//
// Defines for usage in functions and routines                      //
//******************************************************************//
#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ		0x3C1
#define	VGA_MISC_WRITE		0x3C2
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5
#define	VGA_DAC_READ_INDEX	0x3C7
#define	VGA_DAC_WRITE_INDEX	0x3C8
#define	VGA_DAC_DATA		0x3C9
#define	VGA_MISC_READ		0x3CC
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF

#define VGA_CRTC_INDEX		0x3D4
#define VGA_CRTC_DATA		0x3D5
#define	VGA_INSTAT_READ		0x3DA

#define	VGA_NUM_SEQ_REGS	5
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
				VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

//******************************************************************//
// IA-32 Functions and routines                                     //
//******************************************************************//

#define outb(value,port) \
__asm__ ("outb %%al,%%dx"::"a" (value),"d" (port))

#define inb(port) ({ \
unsigned char _v; \
__asm__ volatile ("inb %%dx,%%al":"=a" (_v):"d" (port)); \
_v; \
})

#define cli() __asm__ ("cli");
#define sti() __asm__ ("sti");
#define hlt() __asm__ ("hlt");

void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx)
{
	__asm__ __volatile__(
		"cpuid"
		:
		"=a" (*eax),
		"=b" (*ebx),
		"=c" (*ecx),
		"=d" (*edx)
		:
		"0" (op)
		);
	__asm__ __volatile__ ("" : : : "eax", "ebx", "ecx", "edx");
}

void _memcpy(unsigned int dest,const void *source,unsigned long length)
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

void insl(unsigned short port, unsigned int addr, unsigned long count)
{
	__asm__ __volatile__ ("rep ; insl": "=D"(addr), "=c"(count) : "d"(port), "0"(addr), "1"(count));
}

void outsb(unsigned short port, unsigned int addr, unsigned long count)
{
	__asm__ __volatile__ ("rep ; outsb": "=S"(addr), "=c"(count) : "d"(port), "0"(addr), "1"(count));
}

void outsl(unsigned short port, void * addr, unsigned long count)
{
	__asm__ __volatile__ ("rep ; outsl": "=S"(addr), "=c"(count) : "d"(port), "0"(addr), "1"(count));
}

void insb(unsigned short port, void * addr, unsigned long count)
{
	__asm__ __volatile__ ("rep ; insb": "=D"(addr), "=c"(count) : "d"(port), "0"(addr), "1"(count));
}

//******************************************************************//
// Keyboard and A20 Line                                            //
//******************************************************************//

void reboot()
{
	cli();
	outb(0xFE,0x64);
	hlt();
}

void set_a20()
{
	outb(0xD1,0x64);
	outb(0xDF,0x60);
}

void un_a20()
{
	outb(0xD1,0x64);
	outb(0xDD,0x64);
}

void set_kb()
{
	outb(0xD1,0x64);
	outb(0xAE,0x64);
}

void un_kb()
{
	outb(0xD1,0x64);
	outb(0xAD,0x64);
}

//******************************************************************//
// VGA Text Mode                                                    //
//******************************************************************//

static void vmemwr(unsigned dst_off, unsigned char *src, unsigned count)
{
   _memcpy(dst_off|0xB8000, src, count);
}

unsigned char g_90x30_text[] =
{
// MISC
	0xE7,
// SEQ
	0x03, 0x01, 0x03, 0x00, 0x02,
// CRTC
	0x6B, 0x59, 0x5A, 0x82, 0x60, 0x8D, 0x0B, 0x3E,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x2D, 0x10, 0xE8, 0x05, 0xA3,
	0xFF,
// GC
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
// AC
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};

//---------------//
//8X8 FONTS      //
//---------------//
static unsigned char g_8x8_font[2048] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x7E, 0x81, 0xA5, 0x81, 0xBD, 0x99, 0x81, 0x7E,
	0x7E, 0xFF, 0xDB, 0xFF, 0xC3, 0xE7, 0xFF, 0x7E,
	0x6C, 0xFE, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00,
	0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00,
	0x38, 0x7C, 0x38, 0xFE, 0xFE, 0x92, 0x10, 0x7C,
	0x00, 0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x7C,
	0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00,
	0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF,
	0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00,
	0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF,
	0x0F, 0x07, 0x0F, 0x7D, 0xCC, 0xCC, 0xCC, 0x78,
	0x3C, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18,
	0x3F, 0x33, 0x3F, 0x30, 0x30, 0x70, 0xF0, 0xE0,
	0x7F, 0x63, 0x7F, 0x63, 0x63, 0x67, 0xE6, 0xC0,
	0x99, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x99,
	0x80, 0xE0, 0xF8, 0xFE, 0xF8, 0xE0, 0x80, 0x00,
	0x02, 0x0E, 0x3E, 0xFE, 0x3E, 0x0E, 0x02, 0x00,
	0x18, 0x3C, 0x7E, 0x18, 0x18, 0x7E, 0x3C, 0x18, 
	0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x00, 
	0x7F, 0xDB, 0xDB, 0x7B, 0x1B, 0x1B, 0x1B, 0x00, 
	0x3E, 0x63, 0x38, 0x6C, 0x6C, 0x38, 0x86, 0xFC, 
	0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x00, 
	0x18, 0x3C, 0x7E, 0x18, 0x7E, 0x3C, 0x18, 0xFF,
	0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x00,
	0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00,
	0x00, 0x18, 0x0C, 0xFE, 0x0C, 0x18, 0x00, 0x00, 
	0x00, 0x30, 0x60, 0xFE, 0x60, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFE, 0x00, 0x00, 
	0x00, 0x24, 0x66, 0xFF, 0x66, 0x24, 0x00, 0x00, 
	0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x00, 0x00, 
	0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00,
	0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00, 
	0x18, 0x7E, 0xC0, 0x7C, 0x06, 0xFC, 0x18, 0x00, 
	0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00,
	0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00,
	0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00, 
	0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00,
	0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 
	0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30,
	0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
	0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00,
	0x7C, 0xCE, 0xDE, 0xF6, 0xE6, 0xC6, 0x7C, 0x00, 
	0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00, 
	0x78, 0xCC, 0x0C, 0x38, 0x60, 0xCC, 0xFC, 0x00, 
	0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78, 0x00, 
	0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00, 
	0xFC, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00, 
	0x38, 0x60, 0xC0, 0xF8, 0xCC, 0xCC, 0x78, 0x00,
	0xFC, 0xCC, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00,
	0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78, 0x00, 
	0x78, 0xCC, 0xCC, 0x7C, 0x0C, 0x18, 0x70, 0x00, 
	0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 
	0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30, 
	0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x00, 
	0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00, 
	0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00,
	0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00, 
	0x7C, 0xC6, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00, 
	0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00, 
	0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00, 
	0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00, 
	0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 
	0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00, 
	0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00,
	0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3A, 0x00, 
	0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00, 
	0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 
	0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00, 
	0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00, 
	0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 
	0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00,
	0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00, 
	0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00, 
	0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00, 
	0x7C, 0xC6, 0xC6, 0xC6, 0xD6, 0x7C, 0x0E, 0x00, 
	0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00,
	0x7C, 0xC6, 0xE0, 0x78, 0x0E, 0xC6, 0x7C, 0x00, 
	0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
	0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x00, 
	0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00,
	0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00, 
	0xC6, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0xC6, 0x00, 
	0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x78, 0x00,
	0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00,
	0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00,
	0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00,
	0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00, 
	0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00, 
	0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0xDC, 0x00, 
	0x00, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
	0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00,
	0x00, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00, 
	0x38, 0x6C, 0x64, 0xF0, 0x60, 0x60, 0xF0, 0x00, 
	0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8, 
	0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00, 
	0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00, 
	0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 
	0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00,
	0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 
	0x00, 0x00, 0xCC, 0xFE, 0xFE, 0xD6, 0xD6, 0x00, 
	0x00, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 
	0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x00, 
	0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0, 
	0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E, 
	0x00, 0x00, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x00, 
	0x00, 0x00, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00,
	0x10, 0x30, 0xFC, 0x30, 0x30, 0x34, 0x18, 0x00, 
	0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 
	0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00, 
	0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00, 
	0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00, 
	0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8, 
	0x00, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00,
	0x1C, 0x30, 0x30, 0xE0, 0x30, 0x30, 0x1C, 0x00, 
	0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00, 
	0xE0, 0x30, 0x30, 0x1C, 0x30, 0x30, 0xE0, 0x00, 
	0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0x00,
	0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x0C, 0x06, 0x7C, 
	0x00, 0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
	0x1C, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00, 
	0x7E, 0x81, 0x3C, 0x06, 0x3E, 0x66, 0x3B, 0x00,
	0xCC, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00, 
	0xE0, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00, 
	0x30, 0x30, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
	0x00, 0x00, 0x7C, 0xC6, 0xC0, 0x78, 0x0C, 0x38,
	0x7E, 0x81, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
	0xCC, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
	0xE0, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00, 
	0xCC, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00, 
	0x7C, 0x82, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00, 
	0xE0, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00, 
	0xC6, 0x10, 0x7C, 0xC6, 0xFE, 0xC6, 0xC6, 0x00, 
	0x30, 0x30, 0x00, 0x78, 0xCC, 0xFC, 0xCC, 0x00, 
	0x1C, 0x00, 0xFC, 0x60, 0x78, 0x60, 0xFC, 0x00,
	0x00, 0x00, 0x7F, 0x0C, 0x7F, 0xCC, 0x7F, 0x00,
	0x3E, 0x6C, 0xCC, 0xFE, 0xCC, 0xCC, 0xCE, 0x00, 
	0x78, 0x84, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00, 
	0x00, 0xCC, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00, 
	0x00, 0xE0, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00, 
	0x78, 0x84, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 
	0x00, 0xE0, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 
	0x00, 0xCC, 0x00, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
	0xC3, 0x18, 0x3C, 0x66, 0x66, 0x3C, 0x18, 0x00, 
	0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x00, 
	0x18, 0x18, 0x7E, 0xC0, 0xC0, 0x7E, 0x18, 0x18, 
	0x38, 0x6C, 0x64, 0xF0, 0x60, 0xE6, 0xFC, 0x00, 
	0xCC, 0xCC, 0x78, 0x30, 0xFC, 0x30, 0xFC, 0x30, 
	0xF8, 0xCC, 0xCC, 0xFA, 0xC6, 0xCF, 0xC6, 0xC3, 
	0x0E, 0x1B, 0x18, 0x3C, 0x18, 0x18, 0xD8, 0x70, 
	0x1C, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
	0x38, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00, 
	0x00, 0x1C, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00, 
	0x00, 0x1C, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 
	0x00, 0xF8, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0x00, 
	0xFC, 0x00, 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x00, 
	0x3C, 0x6C, 0x6C, 0x3E, 0x00, 0x7E, 0x00, 0x00, 
	0x38, 0x6C, 0x6C, 0x38, 0x00, 0x7C, 0x00, 0x00,
	0x18, 0x00, 0x18, 0x18, 0x30, 0x66, 0x3C, 0x00, 
	0x00, 0x00, 0x00, 0xFC, 0xC0, 0xC0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xFC, 0x0C, 0x0C, 0x00, 0x00, 
	0xC6, 0xCC, 0xD8, 0x36, 0x6B, 0xC2, 0x84, 0x0F, 
	0xC3, 0xC6, 0xCC, 0xDB, 0x37, 0x6D, 0xCF, 0x03,
	0x18, 0x00, 0x18, 0x18, 0x3C, 0x3C, 0x18, 0x00, 
	0x00, 0x33, 0x66, 0xCC, 0x66, 0x33, 0x00, 0x00,
	0x00, 0xCC, 0x66, 0x33, 0x66, 0xCC, 0x00, 0x00, 
	0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88,
	0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 
	0xDB, 0xF6, 0xDB, 0x6F, 0xDB, 0x7E, 0xD7, 0xED, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
	0x18, 0x18, 0x18, 0x18, 0xF8, 0x18, 0x18, 0x18,
	0x18, 0x18, 0xF8, 0x18, 0xF8, 0x18, 0x18, 0x18,
	0x36, 0x36, 0x36, 0x36, 0xF6, 0x36, 0x36, 0x36,
	0x00, 0x00, 0x00, 0x00, 0xFE, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0xF8, 0x18, 0xF8, 0x18, 0x18, 0x18, 
	0x36, 0x36, 0xF6, 0x06, 0xF6, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0xFE, 0x06, 0xF6, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0xF6, 0x06, 0xFE, 0x00, 0x00, 0x00, 
	0x36, 0x36, 0x36, 0x36, 0xFE, 0x00, 0x00, 0x00,
	0x18, 0x18, 0xF8, 0x18, 0xF8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xF8, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0xFF, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x1F, 0x18, 0x18, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0xFF, 0x18, 0x18, 0x18,
	0x18, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18, 
	0x36, 0x36, 0x36, 0x36, 0x37, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x37, 0x30, 0x3F, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3F, 0x30, 0x37, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0xF7, 0x00, 0xFF, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xFF, 0x00, 0xF7, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x37, 0x30, 0x37, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0x36, 0x36, 0xF7, 0x00, 0xF7, 0x36, 0x36, 0x36, 
	0x18, 0x18, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 
	0x36, 0x36, 0x36, 0x36, 0xFF, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0x18, 0x18, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x3F, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x1F, 0x18, 0x1F, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x3F, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0xFF, 0x36, 0x36, 0x36,
	0x18, 0x18, 0xFF, 0x18, 0xFF, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0xF8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1F, 0x18, 0x18, 0x18, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x76, 0xDC, 0xC8, 0xDC, 0x76, 0x00,
	0x00, 0x78, 0xCC, 0xF8, 0xCC, 0xF8, 0xC0, 0xC0,
	0x00, 0xFC, 0xCC, 0xC0, 0xC0, 0xC0, 0xC0, 0x00,
	0x00, 0x00, 0xFE, 0x6C, 0x6C, 0x6C, 0x6C, 0x00,
	0xFC, 0xCC, 0x60, 0x30, 0x60, 0xCC, 0xFC, 0x00,
	0x00, 0x00, 0x7E, 0xD8, 0xD8, 0xD8, 0x70, 0x00,
	0x00, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0xC0,
	0x00, 0x76, 0xDC, 0x18, 0x18, 0x18, 0x18, 0x00,
	0xFC, 0x30, 0x78, 0xCC, 0xCC, 0x78, 0x30, 0xFC,
	0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x6C, 0x38, 0x00,
	0x38, 0x6C, 0xC6, 0xC6, 0x6C, 0x6C, 0xEE, 0x00,
	0x1C, 0x30, 0x18, 0x7C, 0xCC, 0xCC, 0x78, 0x00,
	0x00, 0x00, 0x7E, 0xDB, 0xDB, 0x7E, 0x00, 0x00,
	0x06, 0x0C, 0x7E, 0xDB, 0xDB, 0x7E, 0x60, 0xC0,
	0x38, 0x60, 0xC0, 0xF8, 0xC0, 0x60, 0x38, 0x00,
	0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
	0x00, 0x7E, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00,
	0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x7E, 0x00,
	0x60, 0x30, 0x18, 0x30, 0x60, 0x00, 0xFC, 0x00,
	0x18, 0x30, 0x60, 0x30, 0x18, 0x00, 0xFC, 0x00,
	0x0E, 0x1B, 0x1B, 0x18, 0x18, 0x18, 0x18, 0x18,
	0x18, 0x18, 0x18, 0x18, 0x18, 0xD8, 0xD8, 0x70,
	0x18, 0x18, 0x00, 0x7E, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x76, 0xDC, 0x00, 0x76, 0xDC, 0x00, 0x00,
	0x38, 0x6C, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
	0x0F, 0x0C, 0x0C, 0x0C, 0xEC, 0x6C, 0x3C, 0x1C,
	0x58, 0x6C, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00,
	0x70, 0x98, 0x30, 0x60, 0xF8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void set_plane(unsigned p)
{
	unsigned char pmask;

	p &= 3;
	pmask = 1 << p;
// set read plane
	outb(4,VGA_GC_INDEX);
	outb(p,VGA_GC_DATA);
// set write plane
	outb(2,VGA_SEQ_INDEX);
	outb(pmask,VGA_SEQ_DATA);
}

void write_regs(unsigned char *regs)
{
	unsigned i;

// Miscellaneous
	outb(*regs,VGA_MISC_WRITE);
	regs++;

// Sequencer
	for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		outb(i,VGA_SEQ_INDEX);
		outb(*regs,VGA_SEQ_DATA);
		regs++;
	}

// Desbloquea el CRTC
	outb(0x03,VGA_CRTC_INDEX);
	outb(inb(VGA_CRTC_DATA) | 0x80,VGA_CRTC_DATA);
	outb(0x11,VGA_CRTC_INDEX);
	outb(inb(VGA_CRTC_DATA) & ~0x80,VGA_CRTC_DATA);

// Nos aseguramos de que se haya desbloqueado
	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;

// Escribe en el CRTC
	for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		outb(i,VGA_CRTC_INDEX);
		outb(*regs,VGA_CRTC_DATA);
		regs++;
	}

// Graphics Controller
	for(i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		outb(i,VGA_GC_INDEX);
		outb(*regs,VGA_GC_DATA);
		regs++;
	}

//Attribute Controller
	for(i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)inb(VGA_INSTAT_READ);
		outb(i,VGA_AC_INDEX);
		outb(*regs,VGA_AC_WRITE);
		regs++;
	}

// Bloquea la paleta de 16 bits
	(void)inb(VGA_INSTAT_READ);
	outb(0x20,VGA_AC_INDEX);
}

static void write_font(unsigned char *buf, unsigned font_height)
{
	unsigned char seq2, seq4, gc4, gc5, gc6;
	unsigned i;
	outb(2,VGA_SEQ_INDEX);
	seq2 = inb(VGA_SEQ_DATA);

	outb(4,VGA_SEQ_INDEX);
	seq4 = inb(VGA_SEQ_DATA);

	outb(seq4 | 0x04,VGA_SEQ_DATA);

	outb(4,VGA_GC_INDEX);
	gc4 = inb(VGA_GC_DATA);

	outb(5,VGA_GC_INDEX);
	gc5 = inb(VGA_GC_DATA);

	outb(gc5 & ~0x10,VGA_GC_DATA);

	outb(VGA_GC_INDEX, 6);
	gc6 = inb(VGA_GC_DATA);

	outb(gc6 & ~0x02,VGA_GC_DATA);

	set_plane(2);

	for(i = 0; i < 256; i++)
	{
		vmemwr(16384u * 0 + i * 32, buf, font_height);
		buf += font_height;
	}

// Devuelve a los registros sus valores iniciales
	outb(2,VGA_SEQ_INDEX);
	outb(seq2,VGA_SEQ_DATA);
	outb(4,VGA_SEQ_INDEX);
	outb(seq4,VGA_SEQ_DATA);
	outb(4,VGA_GC_INDEX);
	outb(gc4,VGA_GC_DATA);
	outb(5,VGA_GC_INDEX);
	outb(gc5,VGA_GC_DATA);
	outb(6,VGA_GC_INDEX);
	outb(gc6,VGA_GC_DATA);
}
