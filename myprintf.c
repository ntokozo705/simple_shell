#include "main.h"

/**
 * myprintf - The print function
 *
 * Return: void.
 */

void my_write(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
