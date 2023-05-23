#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "strings.h"

char *input(char *str) {
  scanf("%s", str);
  return str;
}

int output(char *str) {
  if (printf("%s\n", str) != 0)
    return 0;
  else
    return -1;
}

int is_it_linux(char *str) {
  if (schr(str, '\\') != NULL || schr(str, ':') != NULL)
    return -1;
  return 0;
}

int is_it_windows(char *str) {
  if (schr(str, '/') != NULL)
    return -1;
  if ((((str[0] >= 65 && str[0] <= 90) || (str[0] >= 97 && str[0] <= 122)) &&
       ((str[1] >= 65 && str[1] <= 90) || (str[1] >= 97 && str[1] <= 122)) &&
       str[2] == ':' && str[3] == '\\') ||
      (((str[0] >= 65 && str[0] <= 90) || (str[0] >= 97 && str[0] <= 122)) &&
       str[1] == ':' && str[2] == '\\')) {
    return 0;
  }
  return -1;
}

int symbols_check(char *str) {
  if (schr(str, '*') != NULL || schr(str, '?') != NULL ||
      schr(str, '<') != NULL || schr(str, '>') != NULL ||
      schr(str, '|') != NULL)
    return -1;
  return 0;
}

int error_check(char *str) {
  if (symbols_check(str) != 0) {
    printf("Некорректные символы в пути %s\n", str);
    return -1;
  } else if (slen(str) > MAX_PATH) {
    printf("Превышена максимальная длинна пути %s\n", str);
    return -1;
  } else if (is_it_linux(str) == 0) {
    return 0;
  } else if (is_it_windows(str) != 0) {
    printf("Некорректные символы в Windows пути %s\n", str);
  }
  return 0;
}

char *process(char *str) {
  char *c = sstr(str, "/../");
  if (*c == '0') {
    c = sstr(str, "\\..\\");
  }
  if (*c != '0') {
    delete_parental(c);
  }

  c = sstr(str, "/./");
  if (*c == '0') {
    c = sstr(str, "\\.\\");
  }
  if (*c != '0') {
    delete_current(c);
  }
  return str;
}

char *delete_parental(char *str) {
  delchar(str);
  delchar(str);
  delchar(str);
  delchar(str);
  str--;
  while (*str != '\\' && *str != '/') {
    delchar(str);
    str--;
  }
  return str;
}

char *delete_current(char *str) {
  delchar(str);
  delchar(str);
  return str;
}
