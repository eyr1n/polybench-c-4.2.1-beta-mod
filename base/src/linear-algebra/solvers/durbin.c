#include "linear-algebra/solvers/durbin.h"
#include "polybench.h"
#include <stdio.h>

void init_array_durbin(int n, DATA_TYPE POLYBENCH_1D(r, N, n)) {
  int i, j;

  for (i = 0; i < n; i++) {
    r[i] = (n + 1 - i);
  }
}

void print_array_durbin(int n, DATA_TYPE POLYBENCH_1D(y, N, n)) {
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
