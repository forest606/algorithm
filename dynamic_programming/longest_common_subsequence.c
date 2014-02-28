#include <stdio.h>
#include <string.h>

/*
A[m], B[n]
count[0][i] = 0|1, i = 0, 1, 2, ..., m
count[i][0] = 0|1, i = 0, 1, 2, ..., n
count[i][j] = count[i - 1][j - 1] + 1, 0 < i < m, 0 < j < n, A[i] == B[j]
count[i][j] = max(count[i - 1][j], count[i][j - 1]), 0 < i < m, 0 < j < n, A[i] != B[j]
*/

extern void **malloc_2d_array(size_t row, size_t column, size_t size);
extern void free_2d_array(void **p, size_t row);

#define DEFAULT_VALUE -1
enum {MOVE_LEFT, MOVE_UP, MOVE_DIAGONAL};
char *move = "-I\\";

int lcs_length_recursive(char *astr, char *bstr, int **count, int aindex, int bindex, char **output) {
  int i, amax, bmax;
  if(count[aindex][bindex] == DEFAULT_VALUE) {
    if(aindex == 0) {
      for(i = bindex; i >= 0; --i) {
        if(bstr[i] == astr[aindex]) {
          output[aindex][bindex] = move[MOVE_DIAGONAL];
          return 1;
        }
      }
      return 0;
    }
    if(bindex == 0) {
      for(i = aindex; i >= 0; --i) {
        if(astr[i] == bstr[bindex]) {
          output[aindex][bindex] = move[MOVE_DIAGONAL];
          return 1;
        }
      }
      return 0;
    }

    if(astr[aindex] == bstr[bindex]) {
      count[aindex][bindex] = lcs_length_recursive(astr, bstr, count, aindex - 1, bindex - 1, output) + 1;
      output[aindex][bindex] = move[MOVE_DIAGONAL];
    } else {
      amax = lcs_length_recursive(astr, bstr, count, aindex - 1, bindex, output);
      bmax = lcs_length_recursive(astr, bstr, count, aindex, bindex - 1, output);
      if(amax > bmax) {
        count[aindex][bindex] = amax;
        output[aindex][bindex] = move[MOVE_UP];
      } else {
        count[aindex][bindex] = bmax;
        output[aindex][bindex] = move[MOVE_LEFT];
      }
    }
  }
  return count[aindex][bindex];
}

void print_lcs(char *astr, char **output, int m, int n) {
  if(m == 0 || n == 0)
    return;
  if(output[m][n] == MOVE_UP) {
    print_lcs(astr, output, m - 1, n);
  } else if(output[m][n] == MOVE_LEFT) {
    print_lcs(astr, output, m, n - 1);
  } else {
    print_lcs(astr, output, m - 1, n - 1);
    printf("%c", astr[m]);
  }
}

int lcs_length(char *astr, char *bstr) {
  int **count;
  char **output;
  int alen, blen;
  int i, j, len;

  alen = strlen(astr);
  blen = strlen(bstr);
  count = (int**)malloc_2d_array(alen, blen, sizeof(int));
  for(i = 0; i < alen; ++i) {
    for(j = 0; j < blen; ++j) {
      count[i][j] = DEFAULT_VALUE;
    }
  }

  output = (char**)malloc_2d_array(alen, blen, sizeof(int));
  len = lcs_length_recursive(astr, bstr, count, alen - 1, blen - 1, output);
  /*for(i = 0; i < alen; ++i) {
    for(j = 0; j < blen; ++j) {
      printf("%d  ", count[i][j]);
    }
    printf("\n");
  }

  for(i = 0; i < alen; ++i) {
    for(j = 0; j < blen; ++j) {
      printf("%c  ", output[i][j]);
    }
    printf("\n");
  }*/

  print_lcs(astr, output, alen - 1, blen - 1);
  printf("\n");
  free_2d_array(((void**)count, alen, blen);
  free_2d_array(((void**)output, alen, blen);
  return len;
}

int main() {
  char *astr = "ABCBDAB";
  char *bstr = "BDCABA";
  printf("Max longest common subsequence is %d\n", lcs_length(astr, bstr));
  return 0;
}
