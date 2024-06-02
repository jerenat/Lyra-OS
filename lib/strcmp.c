int strcmp(const char *s,const char *t)
 {
  unsigned char *ss = s;
  unsigned char *tt = t;
  char p;
  int a=0,b=0,c=0;

          while(1){
               a = (int)(p=*ss++);
               b = (int) *tt++;
               c = a - b;
               if(c || !p)break;
          }
  return c;
}