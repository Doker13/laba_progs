#include <inttypes.h>
#include <stdio.h>

#include "coder.h"
#include "command.h"

int encode(uint32_t code_point, CodeUnits *code_units) {
  if (code_point < 0x80) {
    code_units->length = 1;
    code_units->code[0] = code_point;
  } else if (code_point < 0x800) {
    code_units->length = 2;
    code_units->code[0] = 0xc0 | (code_point >> 6);
    code_units->code[1] = 0x80 | (code_point & 0x3f);
  } else if (code_point < 0x10000) {
    code_units->length = 3;
    code_units->code[0] = 0xe0 | (code_point >> 12);
    code_units->code[1] = 0x80 | ((code_point >> 6) & 0x3f);
    code_units->code[2] = 0x80 | (code_point & 0x3f);
  } else if (code_point < 0x200000) {
    code_units->length = 4;
    code_units->code[0] = 0xf0 | (code_point >> 18);
    code_units->code[1] = 0x80 | ((code_point >> 12) & 0x3f);
    code_units->code[2] = 0x80 | ((code_point >> 6) & 0x3f);
    code_units->code[3] = 0x80 | (code_point & 0x3f);
  } else {
    printf("Не удалось закодировать\n");
    return -1;
  }
  return 0;
}

uint32_t decode(const CodeUnits *code_unit) {
  if (code_unit->code[0] < 0x80) {
    return code_unit->code[0];
  } else if (code_unit->code[0] < 0xE0) {
    return ((code_unit->code[0] & 0x1f) << 6) | (code_unit->code[1] & 0x3f);
  } else if (code_unit->code[0] < 0xF0) {
    return ((code_unit->code[0] & 0x0f) << 12) |
           ((code_unit->code[1] & 0x3f) << 6) | (code_unit->code[2] & 0x3f);
  } else if (code_unit->code[0] < 0xF8) {
    return ((code_unit->code[0] & 0x07) << 18) |
           ((code_unit->code[1] & 0x3f) << 12) |
           ((code_unit->code[2] & 0x3f) << 6) | (code_unit->code[3] & 0x3f);
  } else {
    printf("Не удалось декодировать\n");
    return -1;
  }
}

int read_next_code_unit(FILE *in, CodeUnits *code_units) {
  fread(&(code_units->code[0]), 1, 1, in);
  if (code_units->code[0] < 0x80) {
    code_units->length = 1;
    return 0;
  } else if (code_units->code[0] < 0xE0) {
    code_units->length = 2;
    fread(&(code_units->code[1]), 1, 1, in);
    if (code_units->code[1] >= 0x80 && code_units->code[1] <= 0xBF) {
      return 0;
    } else {
      return -1;
    }
  } else if (code_units->code[0] < 0xF0) {
    int count = 0;
    code_units->length = 3;
    for (int i = 1; i < 3; i++) {
      fread(&(code_units->code[i]), 1, 1, in);
      if (code_units->code[i] >= 0x80 && code_units->code[1] <= 0xBF) {
        count++;
      }
    }
    if (count == 2) {
      return 0;
    } else {
      return -1;
    }
  } else if (code_units->code[0] < 0xF8) {
    int count = 0;
    code_units->length = 4;
    for (int i = 1; i < 4; i++) {
      fread(&(code_units->code[i]), 1, 1, in);
      if (code_units->code[i] >= 0x80 && code_units->code[1] <= 0xBF) {
        count++;
      }
    }
    if (count == 3) {
      return 0;
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}

int write_code_unit(FILE *out, const CodeUnits *code_units) {
  return fwrite(code_units->code, 1, code_units->length, out);
}
