CC = gcc 
AS = as
LD = ld
CFLAGS  = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin\
	-fno-stack-protector -I../include
LDFLAGS = -T link.ld

OBJ = atoi.o cls.o kprintf.o printf.o sleep.o strcat.o strcmp.o strcpy.o string.o strlen.o
LC = lib.o
.PHONY: all

all: $(OBJ) $(LC)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

lib.o: 
	$(LD) -r -o lib.o $(OBJ)

