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
	if (strcmp(command, "pwd") == 0)
	{
		char cwd[MAX_INPUT_SIZE];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			my_write(cwd);
			my_write("\n");
		}
		else
			perror("getcwd");
	}
	else if (strcmp(command, "ls") == 0)
	{
		struct dirent entry;
		DIR *dp = opendir(".");
		if (dp == NULL)
		{
			perror("opendir");
			return;
		}
		while ((readdir(dp)) != NULL)
		{
			my_write(entry.d_name);
			my_write("\n");
		}
		closedir(dp);
	}
	else if (strncmp(command, "cat ", 4) == 0)
	{
		const char *file_name = command + 4;
		FILE *file = fopen(file_name, "r");
		if (file != NULL)
		{
			char line[MAX_INPUT_SIZE];
			while (fgets(line, sizeof(line), file))
			{
				my_write(line);
			}
			fclose(file);
		}
		else
			perror("cat");
	}
	else if (strncmp(command, "echo ", 5) == 0)
	{
		const char *message = command + 5;

		my_write(message);
		my_write("\n");
	}
	else
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			return;
		}
		else if (child_pid == 0)
		{
			execlp(command, command, NULL);
			perror("exec");
			exit(1);
		}
		else 
		{
			int status;
			
			waitpid(child_pid, &status, 0);
		}
	}
}
