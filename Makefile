# Variables de comando y banderas
CC = gcc 
AS = as
LD = ld
CFLAGS  = -fno-stack-protector 
LDFLAGS = -T link.ld

# Variables de ruta
BT = boot
KRN = kernel
LB = lib
NAME = oskrnl

# Archivos del $(KRN)
# Lista de archivos en $(KRN) que necesitan compilación
krn_sources := descriptor_tables dma exec executes fat12 floppy gdt interrupt isr kb kernel kheap paging process rand rtc syscall shell time timer

# Lista de archivos en $(LB) que necesitan compilación
lb_sources := atoi cls isdigit printf sleep strcat strcmp strcpy string strlen strrchr strstr strncmp strchr strtok strcspn strncpy sqrt floor cpuid fgets cos sin tan

# Directorios a compilar
SUBDIRS := $(BT) $(KRN) $(LB)

# Regla para compilar todos los subdirectorios
.PHONY: all $(SUBDIRS)
all: $(SUBDIRS) $(NAME)

# Regla para cada subdirectorio
$(SUBDIRS):
	$(MAKE) --directory=$@

# Objetos del kernel
krn_objs := $(foreach obj,$(krn_sources),$(KRN)/$(obj).o)

# Objetos de la librería
lb_objs := $(foreach obj,$(lb_sources),$(LB)/$(obj).o)

# Archivos a linkear
files := $(BT)/boot.o $(krn_objs) $(lb_objs)

# Compilación final del kernel
$(NAME): $(files)
	$(LD) $(LDFLAGS) -o $@ $^
