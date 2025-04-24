#ifndef HSSHELL_H
#define HSSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 1024

extern char **environ;


int main(void);
char *pth_check(char *cmd);
void built_cd(char *args);
void built_exit(char **args, char *line);
void error_ms(char *cmd);
int is_empty(char *str);
void parse_input(char *line, char **args);
int handle_execution(char **args, char *line);
int handle_builtins(char **args, char *line);

#endif
