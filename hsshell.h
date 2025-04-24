#ifndef HSSHELL_H
#define HSSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void);
char *pth_check(char *cmd);
extern char **environ;
void built_cd(char *args);
void built_exit(void);
void error_ms(char *cmd);
#endif
