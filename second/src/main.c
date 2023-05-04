#include <stdio.h>
#include <stdlib.h>

#include "IntVector.h"

void print_vector(intvector *v) {
  printf("Size=%ld Capacity=%ld\nElements:\n", int_vector_get_size(v),
         int_vector_get_capacity(v));
  for (int i = 0; i < int_vector_get_capacity(v); i++) {
    printf("%d ", int_vector_get_item(v, i));
  }
  printf("\n\n");
}

int main() {
  intvector *v = int_vector_new(10);
  printf("Создаём массив v с ёмкостью 10:\n");
  print_vector(v);
  
  for (int i = 0; i < 10; i++) {
    int_vector_set_item(v, i, i);
  }
  printf("Заполняем массив, размер массива теперь также теперь равен 10:\n");
  print_vector(v);
  
  intvector *t = int_vector_copy(v);
  int_vector_free(v);
  printf("Создаём копию структуры v и освобождаем память для вектора v:\n");
  print_vector(t);
  
  printf("Пятый элемент массива: %d\n\n", int_vector_get_item(t, 4));
  
  printf("Добавляем один элемент в конец заполненного массива:\n");
  int_vector_push_back(t, 10);
  print_vector(t);
  
  printf("Удаляем последний элемент массива:\n");
  int_vector_pop_back(t);
  print_vector(t);
  
  printf("Увеличиваем ёмкость до 14:\n");
  int_vector_reserve(t, 14);
  print_vector(t);
  
  printf("Увеличиваем размер до 12:\n");
  int_vector_resize(t, 12);
  print_vector(t);
  
  printf("Уменьшаем ёмкость до 10:\n");
  int_vector_reserve(t, 10);
  print_vector(t);
  
  printf("Уменьшаем размер до 8:\n");
  int_vector_resize(t, 8);
  print_vector(t);
  
  printf("Уменьшаем ёмкость до размера, после чего очищаем память для структуры:\n");
  int_vector_shrink_to_fit(t);
  int_vector_set_item(t, 4, 30);
  print_vector(t);
  
  int_vector_free(t);

  return 0;
}
