#include "linear-algebra/blas/trmm.h"
#include "polybench.h"
#include <stdio.h>

void init_array_trmm(int m, int n, DATA_TYPE *alpha,
                     DATA_TYPE POLYBENCH_2D(A, M, M, m, m),
                     DATA_TYPE POLYBENCH_2D(B, M, N, m, n)) {
  int i, j;

  *alpha = 1.5;
  for (i = 0; i < m; i++) {
    for (j = 0; j < i; j++) {
      A[i][j] = (DATA_TYPE)((i + j) % m) / m;
    }
    A[i][i] = 1.0;
    for (j = 0; j < n; j++) {
      B[i][j] = (DATA_TYPE)((n + (i - j)) % n) / n;
    }
  }
}

void print_array_trmm(int m, int n, DATA_TYPE POLYBENCH_2D(B, M, N, m, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("B");
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      if ((i * m + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, B[i][j]);
    }
  POLYBENCH_DUMP_END("B");
  POLYBENCH_DUMP_FINISH;
}
