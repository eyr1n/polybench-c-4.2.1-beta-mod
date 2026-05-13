#include "linear-algebra/blas/gesummv.h"
#include "polybench.h"
#include <stdio.h>

void init_array_gesummv(int n, DATA_TYPE *alpha, DATA_TYPE *beta,
                        DATA_TYPE POLYBENCH_2D(A, N, N, n, n),
                        DATA_TYPE POLYBENCH_2D(B, N, N, n, n),
                        DATA_TYPE POLYBENCH_1D(x, N, n)) {
  int i, j;

  *alpha = 1.5;
  *beta = 1.2;
  for (i = 0; i < n; i++) {
    x[i] = (DATA_TYPE)(i % n) / n;
    for (j = 0; j < n; j++) {
      A[i][j] = (DATA_TYPE)((i * j + 1) % n) / n;
      B[i][j] = (DATA_TYPE)((i * j + 2) % n) / n;
    }
  }
}

void print_array_gesummv(int n, DATA_TYPE POLYBENCH_1D(y, N, n)) {
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("y");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, y[i]);
  }
  POLYBENCH_DUMP_END("y");
  POLYBENCH_DUMP_FINISH;
}
