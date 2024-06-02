# variables de comando y banderas
CC = gcc 
AS = as
LD = ld
CFLAGS  = -fno-stack-protector 
LDFLAGS = -T link.ld

# variables de ruta
BT = boot
KRN = kernel
LB = lib
NAME = oskrnl

# archivos del $(KRN)
files = $(BT)/boot.o $(KRN)/descriptor_tables.o $(KRN)/dma.o $(KRN)/exec.o $(KRN)/executes.o $(KRN)/fat12.o $(KRN)/floppy.o $(KRN)/gdt.o $(KRN)/interrupt.o $(KRN)/isr.o $(KRN)/kb.o $(KRN)/kernel.o $(KRN)/kheap.o $(KRN)/paging.o $(KRN)/process.o $(KRN)/rand.o $(KRN)/rtc.o $(KRN)/syscall.o $(KRN)/shell.o $(KRN)/time.o $(KRN)/timer.o $(LB)/atoi.o $(LB)/cls.o $(LB)/kprintf.o $(LB)/printf.o $(LB)/sleep.o $(LB)/strcat.o $(LB)/strcmp.o $(LB)/strcpy.o $(LB)/string.o $(LB)/strlen.o

# nombre del kernel
$(KRN) = $(NAME)


.PHONY: all
all: $(files) $($(KRN))

# BOOT/
boot/boot.o:
	$(MAKE) --directory=boot


# KERNEL/
$(KRN)/descriptor_tables.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/dma.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/exec.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/executes.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/fat12.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/floppy.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/gdt.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/interrupt.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/isr.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/kb.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/kernel.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/kheap.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/paging.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/process.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/rand.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/rtc.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/syscall.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/shell.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/time.o:
	$(MAKE) --directory=$(KRN)
$(KRN)/timer.o:
	$(MAKE) --directory=$(KRN)


# /LIB
$(LB)/atoi.o:
	$(MAKE) --directory=$(LB)
$(LB)/cls.o:
	$(MAKE) --directory=$(LB)
$(LB)/kprintf.o:
	$(MAKE) --directory=$(LB)
$(LB)/printf.o:
	$(MAKE) --directory=$(LB)
$(LB)/sleep.o:
	$(MAKE) --directory=$(LB)
$(LB)/strcat.o:
	$(MAKE) --directory=$(LB)
$(LB)/strcmp.o:
	$(MAKE) --directory=$(LB)
$(LB)/strcpy.o:
	$(MAKE) --directory=$(LB)
$(LB)/string.o:
	$(MAKE) --directory=$(LB)
$(LB)/strlen.o:
	$(MAKE) --directory=$(LB)


# kernel compiled
$(NAME):
	$(LD) $(LDFLAGS) -o $(NAME) $(files)	

