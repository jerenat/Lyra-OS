CC = gcc
AS = as
LD = ld
CFLAGS  = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin \
          -fno-stack-protector -I../include
LDFLAGS = -T link.ld

# Lista de archivos objeto
OBJ = descriptor_tables.o dma.o exec.o executes.o fat12.o floppy.o gdt.o ia32.o \
      interrupt.o isr.o kb.o kernel.o kheap.o paging.o process.o rand.o rtc.o \
      shell.o syscall.o time.o timer.o

.PHONY: all clean

# Target principal para compilar todo
all: $(OBJ)

# Regla para compilar archivos C
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Regla para compilar archivos ensamblador
%.o: %.s
	$(AS) -o $@ $<

# Target para limpiar archivos objeto y el ejecutable
clean:
	rm -f $(OBJ)
