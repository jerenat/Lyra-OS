
// linea
int line = 1;

/*-- Similar a PRINTF, pero se usa para entornos del kernel del sistema --*/
void kprintf(char *text, int color)
{
   char *video = (char *)(0xB8000 + (line * 80 * 2));

ret:
   while (*text != 0)
   {

      if (*text == '\n')
      {
         line++;
         char *video = (char *)(0xB8000 + (line * 80 * 2));
         *text++;
         goto ret;
      }

      *video++ = *text++;
      *video++ = 0x0 + color;
   }
   return;
}
