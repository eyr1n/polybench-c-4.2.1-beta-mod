#include "polybench.h"
#include "linear-algebra/blas/symm.h"
#include <stdio.h>

void init_array_symm(int m, int n, DATA_TYPE *alpha, DATA_TYPE *beta,
                     DATA_TYPE POLYBENCH_2D(C, M, N, m, n),
                     DATA_TYPE POLYBENCH_2D(A, M, M, m, m),
                     DATA_TYPE POLYBENCH_2D(B, M, N, m, n)) {
  int i, j;

  *alpha = 1.5;
  *beta = 1.2;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      C[i][j] = (DATA_TYPE)((i + j) % 100) / m;
      B[i][j] = (DATA_TYPE)((n + i - j) % 100) / m;
    }
  for (i = 0; i < m; i++) {
    for (j = 0; j <= i; j++)
      A[i][j] = (DATA_TYPE)((i + j) % 100) / m;
    for (j = i + 1; j < m; j++)
      A[i][j] = -999; // regions of arrays that should not be used
  }
}

void print_array_symm(int m, int n, DATA_TYPE POLYBENCH_2D(C, M, N, m, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("C");
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      if ((i * m + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
    }
  POLYBENCH_DUMP_END("C");
  POLYBENCH_DUMP_FINISH;
}
