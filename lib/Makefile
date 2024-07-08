CC = gcc 
AS = as
LD = ld
CFLAGS  = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin\
	-fno-stack-protector -I../include
LDFLAGS = -T link.ld

OBJ = atoi.o cls.o isdigit.o printf.o sleep.o strcat.o strcmp.o strcpy.o string.o strlen.o strrchr.o strstr.o strncmp.o strchr.o strtok.o strcspn.o strncpy.o sqrt.o floor.o cpuid.o fgets.o
LC = lib.o
.PHONY: all

all: $(OBJ) $(LC)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

lib.o: 
	$(LD) -r -o lib.o $(OBJ)

