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

int main() {
  int i, j;
  int **a;
  float **b;

  a = (int**)malloc_2d_array(2, 3, sizeof(int));
  a[0][0] = 1;
  a[0][1] = 2;
  a[0][2] = 3;
  a[1][0] = 4;
  a[1][1] = 5;
  a[1][2] = 6;
  for(i = 0; i < 2; ++i) {
    for(j = 0; j < 3; ++j) {
      printf("  %d", a[i][j]);
    }
    printf("\n");
  }
  free_2d_array((void **)a, 2);

  b = (float**)malloc_2d_array(2, 2, sizeof(float));
  b[0][0] = 1.1;
  b[0][1] = 2.1;
  b[1][0] = 3.1;
  b[1][1] = 4.1;
  for(i = 0; i < 2; ++i) {
    for(j = 0; j < 2; ++j) {
      printf("  %.2f", b[i][j]);
    }
    printf("\n");
  }
  free_2d_array((void**)b, 2);
  return 0;
}
