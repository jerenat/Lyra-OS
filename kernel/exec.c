void exec(unsigned int addr)
{
    // Código ensamblador en línea
    __asm__ __volatile__("call *%0" : : "a" (addr));
}
