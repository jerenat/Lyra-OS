#include <stdio.h>

size_t strcspn(const char *s1, const char *s2) {
    const char *s = s1;
    const char *accept;

    while (*s) {
        for (accept = s2; *accept; ++accept) {
            if (*s == *accept) {
                break;
            }
        }
        if (*accept == '\0') {
            return s - s1;
        }
        ++s;
    }

    return s - s1;
}
