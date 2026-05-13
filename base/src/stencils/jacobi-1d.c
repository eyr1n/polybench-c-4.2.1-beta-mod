#include "stencils/jacobi-1d.h"
#include "polybench.h"
#include <stdio.h>

void init_array_jacobi_1d(int n, DATA_TYPE POLYBENCH_1D(A, N, n),
                          DATA_TYPE POLYBENCH_1D(B, N, n)) {
  int i;

  for (i = 0; i < n; i++) {
    A[i] = ((DATA_TYPE)i + 2) / n;
    B[i] = ((DATA_TYPE)i + 3) / n;
  }
}

void print_array_jacobi_1d(int n, DATA_TYPE POLYBENCH_1D(A, N, n)) {
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("A");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i]);
  }
  POLYBENCH_DUMP_END("A");
  POLYBENCH_DUMP_FINISH;
}
