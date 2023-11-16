#include "main.h"

/**
 * my_write - The print function
 * @message: message
 * Return: void.
 */

void my_write(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
