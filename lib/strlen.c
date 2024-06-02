int strlen(const char *text)
{
 int i=0;
          while(*text!=0){ //mientras no sea 0 contamos
               *text++;
               i++;
          }
 return i; //retornamos
}