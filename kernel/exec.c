void exec(unsigned int addr)
{
    __asm__ __volatile__("call *%0" : : "a" (addr));
     
}
