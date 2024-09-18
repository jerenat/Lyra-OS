#include <stdio.h>

#define MAXSTRINGLENGTH 4096
#define ERR_NULLPARAMETER -11
#define ERR_BOUNDS -25
int errno;


char *strncpy(char *dest, const char *src, size_t n)
{
    // Check for NULL pointers
    if (dest == NULL || src == NULL)
    {
        errno = ERR_NULLPARAMETER;
        return NULL;
    }

    // Limit maximum length to prevent buffer overflow
    size_t maxLength = n > MAXSTRINGLENGTH ? MAXSTRINGLENGTH : n;

    size_t i;
    for (i = 0; i < maxLength - 1 && src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    // Ensure the destination string is null-terminated
    dest[i] = '\0';

    // Check if the source string was truncated
    if (i >= maxLength - 1 && src[i] != '\0')
    {
        errno = ERR_BOUNDS;
        return NULL;
    }

    return dest;
}
