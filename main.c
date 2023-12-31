#include "main.h"
#include <string.h>

/**
 * main- function call
 *
 * Return: 0 Always.
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
	pid_t pid;

	while (1)
	{
		my_write("S_shell$ ");
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			my_write("\n");
			break;
		}
		input[strlen(input) - 1] = '\0';
		if (strcmp(input, "exit") == 0)
		{
			break;
		}
		execute_command(input);
	}
	return (0);
}
