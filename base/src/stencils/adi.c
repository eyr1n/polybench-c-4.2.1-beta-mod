#include "stencils/adi.h"
#include "polybench.h"
#include <stdio.h>

void init_array_adi(int n, DATA_TYPE POLYBENCH_2D(u, N, N, n, n)) {
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      u[i][j] = (DATA_TYPE)(i + n - j) / n;
    }
}

void print_array_adi(int n, DATA_TYPE POLYBENCH_2D(u, N, N, n, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("u");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if ((i * n + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, u[i][j]);
    }
  POLYBENCH_DUMP_END("u");
  POLYBENCH_DUMP_FINISH;
}
