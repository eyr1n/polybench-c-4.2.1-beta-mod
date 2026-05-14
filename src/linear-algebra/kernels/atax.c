#include "linear-algebra/kernels/atax.h"
#include "polybench.h"
#include <stdio.h>

void init_array_atax(int m, int n, DATA_TYPE POLYBENCH_2D(A, M, N, m, n),
                     DATA_TYPE POLYBENCH_1D(x, N, n)) {
  int i, j;
  DATA_TYPE fn;
  fn = (DATA_TYPE)n;

  for (i = 0; i < n; i++)
    x[i] = 1 + (i / fn);
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      A[i][j] = (DATA_TYPE)((i + j) % n) / (5 * m);
}

void print_array_atax(int n, DATA_TYPE POLYBENCH_1D(y, N, n)) {
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

void kernel_atax(int m, int n, DATA_TYPE POLYBENCH_2D(A, M, N, m, n),
                 DATA_TYPE POLYBENCH_1D(x, N, n),
                 DATA_TYPE POLYBENCH_1D(y, N, n),
                 DATA_TYPE POLYBENCH_1D(tmp, M, m)) {
  int i, j;

#pragma scop
  for (i = 0; i < _PB_N; i++)
    y[i] = 0;
  for (i = 0; i < _PB_M; i++) {
    tmp[i] = SCALAR_VAL(0.0);
    for (j = 0; j < _PB_N; j++)
      tmp[i] = tmp[i] + A[i][j] * x[j];
    for (j = 0; j < _PB_N; j++)
      y[j] = y[j] + A[i][j] * tmp[i];
  }
#pragma endscop
}
