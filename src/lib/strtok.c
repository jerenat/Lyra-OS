#include <stdio.h>
#include <stddef.h>

// Variable estática para mantener el contexto entre llamadas
static char *saveptr;

char *strtok(char *string, const char *delim) {
    // Check parameters
    if (!delim || (string == NULL && saveptr == NULL)) {
        return NULL;
    }

    // Set the starting point
    if (string != NULL) {
        saveptr = string;
    }

    // Skip leading delimiters
    while (*saveptr && strchr(delim, *saveptr)) {
        saveptr++;
    }

    // If reached the end of the string, return NULL
    if (*saveptr == '\0') {
        saveptr = NULL;
        return NULL;
    }

    // Mark the start of the token
    char *token = saveptr;

    // Move to the next delimiter or end of string
    while (*saveptr && !strchr(delim, *saveptr)) {
        saveptr++;
    }

    // If the end of the token is a delimiter, null-terminate the token and advance saveptr
    if (*saveptr) {
        *saveptr = '\0';
        saveptr++;
    }

    return token;
}



char *strtok_r(char *string, const char *delim, char **saveptr) {
    // Check parameters
    if (!delim || (string == NULL && *saveptr == NULL)) {
        return NULL;
    }

    // Set the starting point
    if (string != NULL) {
        *saveptr = string;
    }

    // Skip leading delimiters
    while (**saveptr && strchr(delim, **saveptr)) {
        (*saveptr)++;
    }

    // If reached the end of the string, return NULL
    if (**saveptr == '\0') {
        *saveptr = NULL;
        return NULL;
    }

    // Mark the start of the token
    char *token = *saveptr;

    // Move to the next delimiter or end of string
    while (**saveptr && !strchr(delim, **saveptr)) {
        (*saveptr)++;
    }

    // If the end of the token is a delimiter, null-terminate the token and advance saveptr
    if (**saveptr) {
        **saveptr = '\0';
        (*saveptr)++;
    }

    return token;
}