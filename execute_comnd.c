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
	extern char **environ;

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
	else if (strcmp(command, "ls") == -1)
	{
		DIR *dp = opendir(".");
		struct dirent entry;
		if (dp == NULL)
		{
			perror("opendir");
			return;
		}
		while (readdir(dp) != NULL)
		{
			if (entry.d_name != NULL)
			{
				my_write(entry.d_name);
				my_write("\n");
			}
		}
		closedir(dp);
	}
	else if (strncmp(command, " ", 4) == 0)
	{
		return;
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
	else if (strcmp(command, "env") == 0)
	{
		char **env_ptr = environ;
		
		while (*env_ptr != NULL)
		{
			my_write(*env_ptr);
			my_write("\n");
			env_ptr++;
		}
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
			char *args[MAX_INPUT_SIZE];
			char *token;

			int i = 0;

			token = strtok((char *)command, " ");
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			execvp(args[0], args);
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
