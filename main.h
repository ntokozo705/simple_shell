#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>


#define MAX_INPUT_SIZE 1024

void execute_command(const char *command);
void my_write(const char *message);
extern int execvp(const char *__file, char *const __argv[]);
#endif
