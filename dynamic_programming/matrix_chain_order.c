#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
m[i, i] = 0
m[i, i+1] = p[i-1] * p [i]
m[i, j] = min{m[i, k] + m[k+1, j] + p[i-1] * p[k] * p[j]}, i <= k < j					
m[1, 3]	= min(m[1, 1] + m[2, 3] + p[0] * p[1] * p[3], m[1, 2] + m[3, 3] + p[0] * p[2] * p[3])		
*/

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

long matrix_chain_order(int *dim, int n, int **order) {
  long sum = 0, min, current;
  int step, i, j, k, d;
  int **m;

  m = (int **)malloc_2d_array(n, n, sizeof(int));
  for(step = 1; step < n; ++step) {
    for(i = 0; i < n - step; i++) {
      j = i + step;
      min = LONG_MAX;
      for(k = i; k < j; ++k) {
        current = m[i][k] + m[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
        if(min > current) {
          min = current;
          d = k;
        }
      }
      order[i][j] = d;
      m[i][j] = min;
    }
  }
  sum = m[0][n - 1];
  /*for(i = 0; i < n; ++i) {
    for(j = 0; j < n; ++j) {
      printf("%d  ", m[i][j]);
    }
    printf("\n");
  }*/
  free_2d_array((void **)m, n);

  return sum;
}

void print_optimal_parens(int **order, int i, int j) {
  if(i == j) {
    printf("A[%d]", i);
  } else {
    printf("(");
    print_optimal_parens(order, i, order[i][j]);
    print_optimal_parens(order, order[i][j] + 1, j);
    printf(")");
  }
}

void print_order(int **order, int n) {
  /*int i, j;
  for(i = 0; i < n; ++i) {
    for(j = 0; j < n; ++j) {
      printf("%d  ", order[i][j] + 1);
    }
    printf("\n");
  }*/
  print_optimal_parens(order, 0, n - 1);
  printf("\n");
}

int main() {
  int dim[] = {30, 35, 15, 5, 10, 20, 25};
  int **order;
  long sum;
  int n = sizeof(dim)/sizeof(int) - 1;

  order = (int**)malloc_2d_array(n, n, sizeof(int));
  sum = matrix_chain_order(dim, n, order);
  printf("The least calc number: %ld\n", sum);
  print_order(order, n);
  free_2d_array((void**)order, n);

  return 0;
}
