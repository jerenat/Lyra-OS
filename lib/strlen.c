// -- Contar carácteres de un string
int strlen(const char *text)
{
 int i=0;
          while(*text!=0){ //mientras no sea 0 contamos
               *text++;
               i++;
          }
 return i; //retornamos
}


// -- Contar elementos de un arreglo
int length(const char arr[]) {
    int length = 0;
    while (arr[length] != '\0') {
        length++;
    }
    return length;
}
