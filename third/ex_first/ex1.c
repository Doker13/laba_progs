#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000

size_t encode_varint(uint32_t value, uint8_t *buf) {
  assert(buf != NULL);
  uint8_t *cur = buf;
  while (value >= 0x80) {
    const uint8_t byte = (value & 0x7f) | 0x80;
    *cur = byte;
    value >>= 7;
    ++cur;
  }
  *cur = value;
  ++cur;
  return cur - buf;
}

uint32_t decode_varint(const uint8_t **bufp) {
  const uint8_t *cur = *bufp;
  uint8_t byte = *cur++;
  uint32_t value = byte & 0x7f;
  size_t shift = 7;
  while (byte >= 0x80) {
    byte = *cur++;
    value += (byte & 0x7f) << shift;
    shift += 7;
  }
  *bufp = cur;
  return value;
}

uint32_t generate_number() {
  const int r = rand();
  const int p = r % 100;
  if (p < 90) {
    return r % 128;
  }
  if (p < 95) {
    return r % 16384;
  }
  if (p < 99) {
    return r % 2097152;
  }
  return r % 268435455;
}

int check(char *c, char *unc) {
  FILE *uncomp = fopen(unc, "rb");
  FILE *comp = fopen(c, "rb");
  if (!uncomp || !comp) {
    printf("Файл не найден\n");
    return -1;
  }
  fseek(comp, 0, SEEK_END);
  int size = ftell(comp);
  fseek(comp, 0, SEEK_SET);
  uint8_t *compCheck = malloc(size);
  fread(compCheck, 1, size, comp);
  uint32_t *uncompCheck = malloc(N * 4);
  fread(uncompCheck, 4, N, uncomp);
  const uint8_t *point = compCheck;
  int count = 0;
  for (int i = 0; i < N; i++) {
    if (decode_varint(&point) == uncompCheck[i]) {
      count++;
    }
  }
  fclose(comp);
  fclose(uncomp);
  free(uncompCheck);
  free(compCheck);
  if (count == N) {
    printf("Кодирование успешно\n");
    return 0;
  }
  return -1;
}

int main() {
  char *unc = "uncompressed.dat";
  FILE *uncomp = fopen(unc, "wb");
  char *c = "compressed.dat";
  FILE *comp = fopen(c, "wb");
  if (!uncomp || !comp) {
    printf("Файл не найден\n");
    return -1;
  }
  uint32_t *uncompressed = malloc(N * sizeof(uint32_t));
  for (int i = 0; i < N; i++) {
    uncompressed[i] = generate_number();
  }
  fwrite(uncompressed, sizeof(uint32_t), N, uncomp);
  uint8_t buf[4];
  uint8_t *compressed = malloc(N * 4);
  uint8_t *point = compressed;
  size_t size;
  for (int i = 0; i < N; i++) {
    size = encode_varint(uncompressed[i], buf);
    for (int j = 0; j < size; j++) {
      *compressed = buf[j];
      compressed++;
    }
  }
  fwrite(point, sizeof(uint8_t), compressed - point, comp);
  free(point);
  free(uncompressed);
  fclose(comp);
  fclose(uncomp);
  check(c, unc);
  return 0;
}
