#include "datamining/correlation.h"
#include "polybench.h"
#include <stdio.h>
#include <math.h>

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

void kernel_correlation(int m, int n, DATA_TYPE float_n,
                        DATA_TYPE POLYBENCH_2D(data, N, M, n, m),
                        DATA_TYPE POLYBENCH_2D(corr, M, M, m, m),
                        DATA_TYPE POLYBENCH_1D(mean, M, m),
                        DATA_TYPE POLYBENCH_1D(stddev, M, m)) {
  int i, j, k;

  DATA_TYPE eps = SCALAR_VAL(0.1);

#pragma scop
  for (j = 0; j < _PB_M; j++) {
    mean[j] = SCALAR_VAL(0.0);
    for (i = 0; i < _PB_N; i++)
      mean[j] += data[i][j];
    mean[j] /= float_n;
  }

  for (j = 0; j < _PB_M; j++) {
    stddev[j] = SCALAR_VAL(0.0);
    for (i = 0; i < _PB_N; i++)
      stddev[j] += (data[i][j] - mean[j]) * (data[i][j] - mean[j]);
    stddev[j] /= float_n;
    stddev[j] = SQRT_FUN(stddev[j]);
    /* The following in an inelegant but usual way to handle
       near-zero std. dev. values, which below would cause a zero-
       divide. */
    stddev[j] = stddev[j] <= eps ? SCALAR_VAL(1.0) : stddev[j];
  }

  /* Center and reduce the column vectors. */
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++) {
      data[i][j] -= mean[j];
      data[i][j] /= SQRT_FUN(float_n) * stddev[j];
    }

  /* Calculate the m * m correlation matrix. */
  for (i = 0; i < _PB_M - 1; i++) {
    corr[i][i] = SCALAR_VAL(1.0);
    for (j = i + 1; j < _PB_M; j++) {
      corr[i][j] = SCALAR_VAL(0.0);
      for (k = 0; k < _PB_N; k++)
        corr[i][j] += (data[k][i] * data[k][j]);
      corr[j][i] = corr[i][j];
    }
  }
  corr[_PB_M - 1][_PB_M - 1] = SCALAR_VAL(1.0);
#pragma endscop
}
