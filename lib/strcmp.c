int strcmp(const char *s, const char *t)
{
        while (*s == *t)
        {
                if (*s == '\0')
                {
                        return 0; // Las cadenas son iguales hasta el final
                }
                s++;
                t++;
        }
        return (unsigned char)*s - (unsigned char)*t;
}
