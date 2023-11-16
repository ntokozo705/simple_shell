#include "main.h"
#include <dirent.h>
/**
 * execute_command - The input command exec
 * @command: input
 *
 * Return: void.
 */
void execute_command(const char *command)
{
	pid_t child_pid;
	char *args[MAX_INPUT_SIZE];
	int arg_count;

	if (command == NULL)
	{
		perror("Error reading command");
		exit(EXIT_FAILURE);
	}

	if (strlen(command) == 0)
	{
		return;
	}
	arg_count = 0;

	tokenize_cmd(command, args, &arg_count);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("exec");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(child_pid, &status, 0);
	}
}
