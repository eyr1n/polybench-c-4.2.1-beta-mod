#include "medley/nussinov.h"
#include "polybench.h"
#include <stdio.h>

void init_array_nussinov(int n, base POLYBENCH_1D(seq, N, n),
                         DATA_TYPE POLYBENCH_2D(table, N, N, n, n)) {
  int i, j;

  // base is AGCT/0..3
  for (i = 0; i < n; i++) {
    seq[i] = (base)((i + 1) % 4);
  }

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      table[i][j] = 0;
}

void print_array_nussinov(int n, DATA_TYPE POLYBENCH_2D(table, N, N, n, n)) {
  int i, j;
  int t = 0;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("table");
  for (i = 0; i < n; i++) {
    for (j = i; j < n; j++) {
      if (t % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, table[i][j]);
      t++;
    }
  }
  POLYBENCH_DUMP_END("table");
  POLYBENCH_DUMP_FINISH;
}
