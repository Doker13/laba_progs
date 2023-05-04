#include <stdlib.h>

#include "IntVector.h"

intvector *int_vector_new(size_t initial_capacity) {
  intvector *v = NULL;
  v = malloc(sizeof(*v));
  if (!v)
    return NULL;
  v->data = calloc(initial_capacity, sizeof(int));
  if (!v->data) {
    free(v);
    return NULL;
  }
  v->capacity = initial_capacity;
  return v;
}

intvector *int_vector_copy(const intvector *v) {
  intvector *cpy = NULL;
  cpy = malloc(sizeof(*v));
  cpy->capacity = int_vector_get_capacity(v);
  if (!cpy)
    return NULL;
  cpy->data = calloc(cpy->capacity, sizeof(int));
  if (!cpy->data) {
    free(cpy);
    return NULL;
  }
  for (int i = 0; i < cpy->capacity; i++) {
    cpy->data[i] = v->data[i];
  }
  cpy->capacity = v->capacity;
  cpy->size = v->size;
  return cpy;
}

void int_vector_free(intvector *v) {
  free(v->data);
  free(v);
}

int int_vector_get_item(const intvector *v, size_t index) {
  return v->data[index];
}

void int_vector_set_item(intvector *v, size_t index, int item) {
  if (int_vector_get_size(v) >= index) {
    v->data[index] = item;
  } else if (int_vector_get_size(v) < index && int_vector_get_capacity(v) >= index) { 
    v->data[index] = item;
    v->size = index+1;
  } else {
    int_vector_push_back(v, item);
  }
}

size_t int_vector_get_size(const intvector *v) { return v->size; }

size_t int_vector_get_capacity(const intvector *v) { return v->capacity; }

int int_vector_push_back(intvector *v, int item) {
  if (int_vector_get_size(v) < int_vector_get_capacity(v)) {
    v->data[int_vector_get_size(v)] = item;
    v->size++;
  } else {
    v->capacity += 1;
    v->data = realloc(v->data, v->capacity * sizeof(int));
    if (!v->data) {
      free(v);
      return -1;
    }
    v->data[int_vector_get_size(v)] = item;
    v->size++;
  }
  if (v->data[int_vector_get_size(v)-1] == item)
    return 0;
  else
    return -1;
}

void int_vector_pop_back(intvector *v) {
  if (int_vector_get_size > 0){
    v->data[int_vector_get_size(v)-1] = 0;
    v->size = int_vector_get_size(v)-1;
  }
}

int int_vector_shrink_to_fit(intvector *v) {
  v->capacity = int_vector_get_size(v);
  v->data = realloc(v->data, int_vector_get_capacity(v) * sizeof(int));
  if (!v->data) {
    free(v);
    return -1;
  }
  if (int_vector_get_capacity(v) == int_vector_get_size(v))
    return 0;
  else
    return -1;
}

int int_vector_resize(intvector *v, size_t new_size) {
  if (int_vector_get_size(v) < new_size &&
      new_size < int_vector_get_capacity(v)) {
    v->size = new_size;
  } else if (new_size < int_vector_get_size(v)) {
    for (int i = new_size; i < int_vector_get_size(v); i++) {
      v->data[i] = 0;
    }
    v->size = new_size;
  } else if (new_size > int_vector_get_capacity(v)) {
    v->data = realloc(v->data, new_size * sizeof(int));
    if (!v->data) {
      free(v);
      return -1;
    }
    for (int i = int_vector_get_capacity(v); i < new_size; i++) {
      v->data[i] = 0;
    }
    v->size = new_size;
  }
  if (int_vector_get_size(v) == new_size)
    return 0;
  else
    return -1;
}

int int_vector_reserve(intvector *v, size_t new_capacity) {
  if (new_capacity <= int_vector_get_capacity(v))
    return 0;
  v->data = realloc(v->data, new_capacity * sizeof(int));
  if (!v->data) {
    free(v);
    return -1;
  }
  v->capacity = new_capacity;
  return 0;
}
