#include <stdio.h>
#include <stdlib.h>

#include "IntVector.h"

void print_vector(intvector *v) {
  printf("size=%ld cap=%ld\nEl\n", int_vector_get_size(v),
         int_vector_get_capacity(v));
  for (int i = 0; i < int_vector_get_capacity(v); i++) {
    printf("%d ", int_vector_get_item(v, i));
  }
  printf("\n\n");
}

int main() {
  intvector *v = int_vector_new(8);
  for (int i = 0; i < 20; i++) {
    int_vector_set_item(v, i, i);
  }
  print_vector(v);

  intvector *t = int_vector_copy(v);
  print_vector(t);
  int_vector_free(t);
  
  printf("%d\n", int_vector_get_item(v, 4));
  
  int_vector_push_back(v, 11);
  print_vector(v);
  int_vector_free(v);

  return 0;
}
