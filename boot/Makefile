CC = gcc 
AS = as
LD = ld
CFLAGS  = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin\
	-fno-stack-protector -I../include
LDFLAGS = -T link.ld

OBJ = boot.o

.PHONY: all

all: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

