#include "linear-algebra/kernels/mvt.h"
#include "polybench.h"
#include <stdio.h>

void init_array_mvt(int n, DATA_TYPE POLYBENCH_1D(x1, N, n),
                    DATA_TYPE POLYBENCH_1D(x2, N, n),
                    DATA_TYPE POLYBENCH_1D(y_1, N, n),
                    DATA_TYPE POLYBENCH_1D(y_2, N, n),
                    DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
  int i, j;

  for (i = 0; i < n; i++) {
    x1[i] = (DATA_TYPE)(i % n) / n;
    x2[i] = (DATA_TYPE)((i + 1) % n) / n;
    y_1[i] = (DATA_TYPE)((i + 3) % n) / n;
    y_2[i] = (DATA_TYPE)((i + 4) % n) / n;
    for (j = 0; j < n; j++)
      A[i][j] = (DATA_TYPE)(i * j % n) / n;
  }
}

void print_array_mvt(int n, DATA_TYPE POLYBENCH_1D(x1, N, n),
                     DATA_TYPE POLYBENCH_1D(x2, N, n)) {
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("x1");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, x1[i]);
  }
  POLYBENCH_DUMP_END("x1");

  POLYBENCH_DUMP_BEGIN("x2");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, x2[i]);
  }
  POLYBENCH_DUMP_END("x2");
  POLYBENCH_DUMP_FINISH;
}

void kernel_mvt(int n, DATA_TYPE POLYBENCH_1D(x1, N, n),
                DATA_TYPE POLYBENCH_1D(x2, N, n),
                DATA_TYPE POLYBENCH_1D(y_1, N, n),
                DATA_TYPE POLYBENCH_1D(y_2, N, n),
                DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
  int i, j;

#pragma scop
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_N; j++)
      x1[i] = x1[i] + A[i][j] * y_1[j];
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_N; j++)
      x2[i] = x2[i] + A[j][i] * y_2[j];
#pragma endscop
}
