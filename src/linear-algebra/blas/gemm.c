#include "linear-algebra/blas/gemm.h"
#include "polybench.h"
#include <stdio.h>

void init_array_gemm(int ni, int nj, int nk, DATA_TYPE *alpha, DATA_TYPE *beta,
                     DATA_TYPE POLYBENCH_2D(C, NI, NJ, ni, nj),
                     DATA_TYPE POLYBENCH_2D(A, NI, NK, ni, nk),
                     DATA_TYPE POLYBENCH_2D(B, NK, NJ, nk, nj)) {
  int i, j;

  *alpha = 1.5;
  *beta = 1.2;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
      C[i][j] = (DATA_TYPE)((i * j + 1) % ni) / ni;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nk; j++)
      A[i][j] = (DATA_TYPE)(i * (j + 1) % nk) / nk;
  for (i = 0; i < nk; i++)
    for (j = 0; j < nj; j++)
      B[i][j] = (DATA_TYPE)(i * (j + 2) % nj) / nj;
}

void print_array_gemm(int ni, int nj,
                      DATA_TYPE POLYBENCH_2D(C, NI, NJ, ni, nj)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("C");
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++) {
      if ((i * ni + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
    }
  POLYBENCH_DUMP_END("C");
  POLYBENCH_DUMP_FINISH;
}

void kernel_gemm(int ni, int nj, int nk, DATA_TYPE alpha, DATA_TYPE beta,
                 DATA_TYPE POLYBENCH_2D(C, NI, NJ, ni, nj),
                 DATA_TYPE POLYBENCH_2D(A, NI, NK, ni, nk),
                 DATA_TYPE POLYBENCH_2D(B, NK, NJ, nk, nj)) {
  int i, j, k;

// BLAS PARAMS
// TRANSA = 'N'
// TRANSB = 'N'
//  => Form C := alpha*A*B + beta*C,
// A is NIxNK
// B is NKxNJ
// C is NIxNJ
#pragma scop
  for (i = 0; i < _PB_NI; i++) {
    for (j = 0; j < _PB_NJ; j++)
      C[i][j] *= beta;
    for (k = 0; k < _PB_NK; k++) {
      for (j = 0; j < _PB_NJ; j++)
        C[i][j] += alpha * A[i][k] * B[k][j];
    }
  }
#pragma endscop
}
