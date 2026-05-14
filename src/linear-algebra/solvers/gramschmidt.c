#include "linear-algebra/solvers/gramschmidt.h"
#include "polybench.h"
#include <stdio.h>
#include <math.h>

void init_array_gramschmidt(int m, int n, DATA_TYPE POLYBENCH_2D(A, M, N, m, n),
                            DATA_TYPE POLYBENCH_2D(R, N, N, n, n),
                            DATA_TYPE POLYBENCH_2D(Q, M, N, m, n)) {
  int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      A[i][j] = (((DATA_TYPE)((i * j) % m) / m) * 100) + 10;
      Q[i][j] = 0.0;
    }
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      R[i][j] = 0.0;
}

void print_array_gramschmidt(int m, int n,
                             DATA_TYPE POLYBENCH_2D(A, M, N, m, n),
                             DATA_TYPE POLYBENCH_2D(R, N, N, n, n),
                             DATA_TYPE POLYBENCH_2D(Q, M, N, m, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("R");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if ((i * n + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, R[i][j]);
    }
  POLYBENCH_DUMP_END("R");

  POLYBENCH_DUMP_BEGIN("Q");
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      if ((i * n + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, Q[i][j]);
    }
  POLYBENCH_DUMP_END("Q");
  POLYBENCH_DUMP_FINISH;
}

void kernel_gramschmidt(int m, int n, DATA_TYPE POLYBENCH_2D(A, M, N, m, n),
                        DATA_TYPE POLYBENCH_2D(R, N, N, n, n),
                        DATA_TYPE POLYBENCH_2D(Q, M, N, m, n)) {
  int i, j, k;

  DATA_TYPE nrm;

#pragma scop
  for (k = 0; k < _PB_N; k++) {
    nrm = SCALAR_VAL(0.0);
    for (i = 0; i < _PB_M; i++)
      nrm += A[i][k] * A[i][k];
    R[k][k] = SQRT_FUN(nrm);
    for (i = 0; i < _PB_M; i++)
      Q[i][k] = A[i][k] / R[k][k];
    for (j = k + 1; j < _PB_N; j++) {
      R[k][j] = SCALAR_VAL(0.0);
      for (i = 0; i < _PB_M; i++)
        R[k][j] += Q[i][k] * A[i][j];
      for (i = 0; i < _PB_M; i++)
        A[i][j] = A[i][j] - Q[i][k] * R[k][j];
    }
  }
#pragma endscop
}
