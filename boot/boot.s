.equ MULTIBOOT_HEADER_MAGIC,     0x1BADB002
.equ MULTIBOOT_HEADER_FLAGS,     0x00010003



.section .text
.globl start
.extern  code, bss, end, main



.align 4

mboot:
	
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_FLAGS
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	.long mboot
	.long code
	.long bss
	.long end
	.long start

start:
	pushl %ebx  
	cli       
	call main 

