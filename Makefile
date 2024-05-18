CC = gcc 
AS = as
LD = ld
CFLAGS  = -fno-stack-protector 
LDFLAGS = -T link.ld

# archivos del kernel
files = boot/boot.o kernel/descriptor_tables.o kernel/dma.o kernel/exec.o kernel/fat12.o kernel/floppy.o kernel/gdt.o kernel/interrupt.o kernel/isr.o kernel/kb.o kernel/kernel.o kernel/kheap.o kernel/paging.o kernel/process.o kernel/shell.o kernel/syscall.o kernel/timer.o lib/atoi.o lib/cls.o lib/kprintf.o lib/printf.o lib/sleep.o lib/strcat.o lib/strcmp.o lib/strcpy.o lib/string.o lib/strlen.o

# nombre del kernel
KERNEL = Luxur


.PHONY: all
all: $(files) $(KERNEL)

# BOOT/
boot/boot.o:
	$(MAKE) --directory=boot


# KERNEL/
kernel/descriptor_tables.o:
	$(MAKE) --directory=kernel
kernel/dma.o:
	$(MAKE) --directory=kernel
kernel/exec.o:
	$(MAKE) --directory=kernel
kernel/fat12.o:
	$(MAKE) --directory=kernel
kernel/floppy.o:
	$(MAKE) --directory=kernel
kernel/gdt.o:
	$(MAKE) --directory=kernel
kernel/interrupt.o:
	$(MAKE) --directory=kernel
kernel/isr.o:
	$(MAKE) --directory=kernel
kernel/kb.o:
	$(MAKE) --directory=kernel
kernel/kernel.o:
	$(MAKE) --directory=kernel
kernel/kheap.o:
	$(MAKE) --directory=kernel
kernel/paging.o:
	$(MAKE) --directory=kernel
kernel/process.o:
	$(MAKE) --directory=kernel
kernel/shell.o:
	$(MAKE) --directory=kernel
kernel/syscall.o:
	$(MAKE) --directory=kernel
kernel/timer.o:
	$(MAKE) --directory=kernel


# /LIB
lib/atoi.o:
	$(MAKE) --directory=lib
lib/cls.o:
	$(MAKE) --directory=lib
lib/kprintf.o:
	$(MAKE) --directory=lib
lib/printf.o:
	$(MAKE) --directory=lib
lib/sleep.o:
	$(MAKE) --directory=lib
lib/strcat.o:
	$(MAKE) --directory=lib
lib/strcmp.o:
	$(MAKE) --directory=lib
lib/strcpy.o:
	$(MAKE) --directory=lib
lib/string.o:
	$(MAKE) --directory=lib
lib/strlen.o:
	$(MAKE) --directory=lib


# Kernel compiled
Luxur:
	$(LD) $(LDFLAGS) -o Luxur $(files)	

