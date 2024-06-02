

.globl limpiar_gdt, limpiar_idt 

limpiar_gdt:
    movl 4(%esp),%eax  
    lgdt (%eax)     

    movw $0x10,%ax     
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ss
    jmp $0x08, $flush  
flush:
    ret

limpiar_idt:
    movl 4(%esp),%eax  
     lidt (%eax)      
    ret

