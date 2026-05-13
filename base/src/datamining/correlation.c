#include "datamining/correlation.h"
#include "polybench.h"
#include <stdio.h>

void init_array_correlation(int m, int n, DATA_TYPE *float_n,
                            DATA_TYPE POLYBENCH_2D(data, N, M, n, m)) {
  int i, j;

  *float_n = (DATA_TYPE)N;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      data[i][j] = (DATA_TYPE)(i * j) / M + i;
}

void print_array_correlation(int m, DATA_TYPE POLYBENCH_2D(corr, M, M, m, m)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("corr");
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      if ((i * m + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, corr[i][j]);
    }
  POLYBENCH_DUMP_END("corr");
  POLYBENCH_DUMP_FINISH;
}
