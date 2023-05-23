#pragma once

#define MAX_PATH 260

char *input(char *str);
int output(char *str);
int is_it_linux(char *str);
int is_it_windows(char *str);
int error_check(char *str);
int symbols_check(char *str);
char *process(char *str);
char *delete_parental(char *str);
char *delete_current(char *str);
