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

	if (command == NULL)
	{
		perror("Error reading command");
		exit(EXIT_FAILURE);
	}

	if (strlen(command) == 0)
	{
		return;
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[2];

		args[0] = (char *)command;
		args[1] = NULL;

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
