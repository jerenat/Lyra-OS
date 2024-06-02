

.global read_eip, copy_page_physical, looper


read_eip: 
    popl %eax                   
    jmp *%eax                   
                                


copy_page_physical: 
    pushl %ebx           
    pushf                 
                          
    cli                   
                          
    movl 12(%esp),%ebx    
    movl 16(%esp),%ecx   

    movl %cr0, %edx      
    andl $0x7fffffff,%edx 
    movl %edx, %cr0      

    movl $1024,%edx       # 1024*4bytes = 4096 bytes

looper: 
    movl %ebx,%eax      
    movl %eax,%ecx     
    addl $4,%ebx          
    addl $4,%ecx          
    decl %edx             
    jnz looper

    movl %cr0, %edx       
    orl $0x80000000,%edx  
    movl %edx, %cr0       

    popf                 
    popl %ebx            
