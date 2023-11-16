#include "main.h"

/**
 * tokenize_cmd - Tokenizes the command line.
 * @command_line: The input command line.
 * @args: Array to store tokens.
 * @arg_count: Pointer to store the number of arguments.
 *
 * Return: void.
 */
void tokenize_cmd(const char *command_line, char **args, int *arg_count)
{
	char *token;

	if (command_line == NULL || args == NULL || arg_count == NULL)
	{
		return;
	}
	token = strtok((char *)command_line, " ");
	*arg_count = 0;

	while (token != NULL)
	{
		args[(*arg_count)++] = strdup(token);
		token = strtok(NULL, " ");
	}

	args[*arg_count] = NULL;
}
