
int strcpy(char *dest,const char *org)
 {
 char tk;
 int i=0;
         do{
            *dest++ = tk = *org++;
            i++;
           }while(tk);
 return i;
 }