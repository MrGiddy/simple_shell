#ifndef MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
int _strlen(char *str);
int _puts(char *str);
void display_prompt(void);
char *_strdup(char *str);
char **toknize(char *command, char *delimiter);
char *_strcpy(char *dest, char *src);

#endif /* MAIN_H */
