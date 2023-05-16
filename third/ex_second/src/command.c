#include "coder.h"
#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name) {
  FILE *input = fopen(in_file_name, "r");
  FILE *output = fopen(out_file_name, "wb");
  if (!input || !output) {
    printf("Файл не найден\n");
    return -1;
  }

  uint32_t hex;
  CodeUnits codeunit;
  while (fscanf(input, "%" SCNx32, &hex) == 1) {
    if (encode(hex, &codeunit) == 0) {
      write_code_unit(output, &codeunit);
    } else {
      return -1;
    }
  }
  fclose(input);
  fclose(output);
  printf("Успешно\n");
  return 0;
}

int decode_file(const char *in_file_name, const char *out_file_name) {
  FILE *input = fopen(in_file_name, "rb");
  FILE *output = fopen(out_file_name, "w");
  if (!input || !output) {
    printf("Файл не найден\n");
    return -1;
  }

  fseek(input, 0, SEEK_END);
  int size = ftell(input);
  fseek(input, 0, SEEK_SET);
  while (ftell(input) != size) {
    CodeUnits codeunit;
    if (read_next_code_unit(input, &codeunit) == 0) {
      fprintf(output, "%" PRIx32 "\n", decode(&codeunit));
    } else {
      continue;
    }
  }
  fclose(input);
  fclose(output);
  printf("Успешно\n");
  return 0;
}
