#include <stdio.h>
#include <string.h>

#include "coder.h"
#include "command.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Неверное количество аргументов\n");
    return -1;
  }
  if (strcmp(argv[1], "decode") == 0) {
    decode_file(argv[2], argv[3]);
  } else if (strcmp(argv[1], "encode") == 0) {
    encode_file(argv[2], argv[3]);
  } else {
    printf("Неверная команда, используйте encode/decode\n");
    return -1;
  }
  return 0;
}
