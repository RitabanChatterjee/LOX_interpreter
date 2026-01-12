#ifndef DYNAMIC_ARRAYS_H
#define DYNAMIC_ARRAYS_H

#include <stdlib.h>
#include <stdio.h>

#define DEFINE_ARRAY(type, name)                                  \
typedef struct {                                                  \
    type* data;                                                   \
    size_t size;                                                  \
    size_t capacity;                                              \
} name;                                                           \
                                                                  \
static inline name name##_make(void) {                            \
    name a;                                                       \
    a.size = 0;                                                   \
    a.capacity = 8;                                               \
    a.data = malloc(a.capacity * sizeof(type));                  \
    if (!a.data) {                                                \
        fprintf(stderr, "out of memory\n");                       \
        exit(1);                                                  \
    }                                                             \
    return a;                                                     \
}                                                                 \
                                                                  \
static inline void name##_free(name* a) {                         \
    free(a->data);                                                \
    a->data = NULL;                                               \
    a->size = 0;                                                  \
    a->capacity = 0;                                              \
}                                                                 \
                                                                  \
static inline void name##_push(name* a, type value) {             \
    if (a->size == a->capacity) {                                 \
        a->capacity *= 2;                                         \
        type* new = realloc(a->data, a->capacity * sizeof(type));\
        if (!new) {                                               \
            fprintf(stderr, "out of memory\n");                   \
            exit(1);                                              \
        }                                                         \
        a->data = new;                                            \
    }                                                             \
    a->data[a->size++] = value;}\

#endif /* ARRAY_H */
