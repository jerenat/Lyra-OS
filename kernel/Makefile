CC = gcc 
AS = as
LD = ld
CFLAGS  = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin\
	-fno-stack-protector -I../include
LDFLAGS = -T link.ld

OBJ = descriptor_tables.o dma.o exec.o fat12.o floppy.o gdt.o ia32.o interrupt.o isr.o kb.o kernel.o kheap.o paging.o process.o shell.o syscall.o timer.o

.PHONY: all

all: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

