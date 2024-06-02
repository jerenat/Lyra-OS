void strcat(char *dest, const char *org)
{
        while(*dest!=0){
             ++dest;
        }
            while (*org!=0){
             *dest++ = *org++;
            }
}