#pragma once

typedef struct
{
    int* data;
    size_t size;
    size_t capacity;
} intvector;

intvector *int_vector_new(size_t initial_capacity);
intvector *int_vector_copy(const intvector *v);
void int_vector_free(intvector *v);
int int_vector_get_item(const intvector *v, size_t index);
void int_vector_set_item(intvector *v,size_t index, int item);
size_t int_vector_get_size(const intvector *v);
size_t int_vector_get_capacity(const intvector *v);
int int_vector_push_back(intvector *v, int item);
void int_vector_pop_back(intvector *v);
int int_vector_shrink_to_fit(intvector *v);
int int_vector_resize(intvector *v,size_t new_size);
int int_vector_reserve(intvector *v,size_t new_capacity);
