#include "main.h"

/**
 * b_free - free a pointer
 * @ptr: pointer address
 *
 * Return: 1 if freed, otherwise 0.
 */

int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
