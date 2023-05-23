#pragma once

#include <stdio.h>

#define MAX_PATH 260

size_t slen(char *str);
int scmp(char *str1, char *str2);
char *scpy(char *str1, char *str2);
char* stok(char *str, char *delim);
char *schr(char *str, char c);
int is_del(char c, char *delim);
void delchar(char *str);
char *scat(char *str1, char *str2);
char *sstr(char *str, char *ptr);
int compare(char *str, char *ptr);
