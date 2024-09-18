#include <stdio.h>
char *strchr(const char *string, int character)
{
	// Convert character to char type once for clarity
	char char_to_find = (char) character;

	// Loop through the string
	while (*string)
	{
		if (*string == char_to_find)
			return (char *) string;

		string++;
	}

	// Check for the null terminator if character is '\0'
	if (char_to_find == '\0')
		return (char *) string;

	// Return failure
	return NULL;
}
