#include "datamining/covariance.h"
#include "polybench.h"
#include <stdio.h>

void init_array_covariance(int m, int n, DATA_TYPE *float_n,
                           DATA_TYPE POLYBENCH_2D(data, N, M, n, m)) {
  int i, j;

  *float_n = (DATA_TYPE)n;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      data[i][j] = ((DATA_TYPE)i * j) / M;
}

void print_array_covariance(int m, DATA_TYPE POLYBENCH_2D(cov, M, M, m, m)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("cov");
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      if ((i * m + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, cov[i][j]);
    }
  POLYBENCH_DUMP_END("cov");
  POLYBENCH_DUMP_FINISH;
}
