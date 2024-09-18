/* --- CABECERA DE MANEJO DE STRINGS --- */

int strlen(const char *text); 
int strcmp(const char *s,const char *t);	// compara carácterres
int strncmp(const char *s1, const char *s2, size_t length);
int strcpy(char *dest,const char *org);		// copiar string
char *strrchr(const char *string, int character);
char *strchr(const char *string, int character);
char *strstr(const char *s1, const char *s2);
char *strtok(char *string, const char *delim);
char *strtok_r(char *string, const char *delim, char **saveptr);
size_t strcspn(const char *s1, const char *s2);
char *strncpy(char *dest, const char *src, size_t n);