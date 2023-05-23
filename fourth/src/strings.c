#include <stdio.h>

#include "strings.h"

size_t slen(char *str) {
  size_t len = 0;
  for (int i = 0; str[i] != '\0'; i++)
    len++;
  return len;
}

char *stok(char *str, char *delim) {
  static char *p;
  if (!str) {
    str = p;
  }
  if (!str) {
    return NULL;
  }
  while (1) {
    if (is_del(*str, delim)) {
      str++;
      continue;
    }
    if (*str == '\0') {
      return NULL;
    }
    break;
  }
  char *tmp = str;
  while (1) {
    if (*str == '\0') {
      p = str;
      return tmp;
    }
    if (is_del(*str, delim)) {
      *str = '\0';
      p = str + 1;
      return tmp;
    }
    str++;
  }
}

char *scpy(char *str1, char *str2) {
  if (str1 == NULL) {
    return NULL;
  }
  int len = slen(str1);
  for (int i = 0; i < len; i++) {
    str2[i] = str1[i];
  }
  str2[len] = '\0';
  return str2;
}

int scmp(char *str1, char *str2) {
  while (*str1) {
    if (*str1 != *str2)
      break;
    str1++;
    str2++;
  }
  if ((*str1 - *str2) > 0)
    return 1;
  else if ((*str1 - *str2) < 0)
    return -1;
  return 0;
}

char *schr(char *str, char c) {
  while (*str != c && *str != '\0')
    str++;
  if (*str == c)
    return str;
  else
    return NULL;
}

int is_del(char c, char *delim) {
  while (*delim != '\0') {
    if (c == *delim)
      return 1;
    delim++;
  }
  return 0;
}

void delchar(char *str) {
  for (int i = 0; i < slen(str); ++i)
    str[i] = str[i + 1];
}

char *scat(char *str1, char *str2) {
  char *ptr = str1 + slen(str1);
  while (*str2 != '\0') {
    *ptr++ = *str2++;
  }
  *ptr = '\0';
  return str1;
}

char *sstr(char *str, char *ptr) {
  while (*str != '\0') {
    if ((*str == *ptr) && compare(str, ptr)) {
      return str;
    }
    str++;
  }

  return "0";
}

int compare(char *str, char *ptr) {
  while (*str != '\0' && *ptr != '\0') {
    if (*str != *ptr) {
      return 0;
    }
    str++;
    ptr++;
  }
  if (*ptr == '\0') {
    return 1;
  }
  return 0;
}
