#include <stdio.h>
#include <stdlib.h>

void **malloc_2d_array(size_t row, size_t column, size_t size) {
  int i, j;
  void **p;

  p = (void**)malloc(sizeof(void*) * row);
  if(p == NULL)
    return NULL;
  for(i = 0; i < row; ++i) {
    p[i] = calloc(row * column, size);
    if(p[i] == NULL) {
      for(j = 0; j < i; ++j)
        free(p[j]);
      free(p);
      return NULL;
    }
  }

  return p;
}

void free_2d_array(void **p, size_t row) {
  int i;
  if(*p) {
    for(i = 0; i < row; ++i)
      free(p[i]);
    free(p);
  }
}
