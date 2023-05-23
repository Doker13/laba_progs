#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "strings.h"

int main() {
  char *delim = malloc(1);
  char *in = malloc(MAX_PATH * 12);
  char *out = malloc(MAX_PATH * 12);
  char *tmp = malloc(MAX_PATH);
  printf("delim: ");
  input(delim);
  printf("paths: ");
  input(in);
  tmp = stok(in, delim);
  while (tmp != NULL){
    if (error_check(tmp) == 0){
      tmp = process(tmp);
      scat(out, "+");
      scat(out, tmp);
    } else {
      return -1;
    }
    tmp = stok(NULL, delim);
  }
  delchar(out);
  output(out);
  free(tmp);
  free(out);
  free(in);
  free(delim);
  return 0;
}
