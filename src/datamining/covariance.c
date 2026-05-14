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

void kernel_covariance(int m, int n, DATA_TYPE float_n,
                       DATA_TYPE POLYBENCH_2D(data, N, M, n, m),
                       DATA_TYPE POLYBENCH_2D(cov, M, M, m, m),
                       DATA_TYPE POLYBENCH_1D(mean, M, m)) {
  int i, j, k;

#pragma scop
  for (j = 0; j < _PB_M; j++) {
    mean[j] = SCALAR_VAL(0.0);
    for (i = 0; i < _PB_N; i++)
      mean[j] += data[i][j];
    mean[j] /= float_n;
  }

  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++)
      data[i][j] -= mean[j];

  for (i = 0; i < _PB_M; i++)
    for (j = i; j < _PB_M; j++) {
      cov[i][j] = SCALAR_VAL(0.0);
      for (k = 0; k < _PB_N; k++)
        cov[i][j] += data[k][i] * data[k][j];
      cov[i][j] /= (float_n - SCALAR_VAL(1.0));
      cov[j][i] = cov[i][j];
    }
#pragma endscop
}
