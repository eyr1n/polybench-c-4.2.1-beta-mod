#include "linear-algebra/solvers/trisolv.h"
#include "polybench.h"
#include <stdio.h>

void init_array_trisolv(int n, DATA_TYPE POLYBENCH_2D(L, N, N, n, n),
                        DATA_TYPE POLYBENCH_1D(x, N, n),
                        DATA_TYPE POLYBENCH_1D(b, N, n)) {
  int i, j;

  for (i = 0; i < n; i++) {
    x[i] = -999;
    b[i] = i;
    for (j = 0; j <= i; j++)
      L[i][j] = (DATA_TYPE)(i + n - j + 1) * 2 / n;
  }
}

void print_array_trisolv(int n, DATA_TYPE POLYBENCH_1D(x, N, n)) {
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("x");
  for (i = 0; i < n; i++) {
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, x[i]);
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
  }
  POLYBENCH_DUMP_END("x");
  POLYBENCH_DUMP_FINISH;
}

void kernel_trisolv(int n, DATA_TYPE POLYBENCH_2D(L, N, N, n, n),
                    DATA_TYPE POLYBENCH_1D(x, N, n),
                    DATA_TYPE POLYBENCH_1D(b, N, n)) {
  int i, j;

#pragma scop
  for (i = 0; i < _PB_N; i++) {
    x[i] = b[i];
    for (j = 0; j < i; j++)
      x[i] -= L[i][j] * x[j];
    x[i] = x[i] / L[i][i];
  }
#pragma endscop
}
