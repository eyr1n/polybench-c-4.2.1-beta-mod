#include "linear-algebra/blas/syrk.h"
#include "polybench.h"
#include <stdio.h>

void init_array_syrk(int n, int m, DATA_TYPE *alpha, DATA_TYPE *beta,
                     DATA_TYPE POLYBENCH_2D(C, N, N, n, n),
                     DATA_TYPE POLYBENCH_2D(A, N, M, n, m)) {
  int i, j;

  *alpha = 1.5;
  *beta = 1.2;
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      A[i][j] = (DATA_TYPE)((i * j + 1) % n) / n;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      C[i][j] = (DATA_TYPE)((i * j + 2) % m) / m;
}

void print_array_syrk(int n, DATA_TYPE POLYBENCH_2D(C, N, N, n, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("C");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if ((i * n + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
    }
  POLYBENCH_DUMP_END("C");
  POLYBENCH_DUMP_FINISH;
}
