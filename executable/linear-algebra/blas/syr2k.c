#include "linear-algebra/blas/syr2k.h"
#include "polybench.h"
#include <string.h>

int main(int argc, char **argv) {
  /* Retrieve problem size. */
  int n = N;
  int m = M;

  /* Variable declaration/allocation. */
  DATA_TYPE alpha;
  DATA_TYPE beta;
  POLYBENCH_2D_ARRAY_DECL(C, DATA_TYPE, N, N, n, n);
  POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, M, n, m);
  POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, M, n, m);

  /* Initialize array(s). */
  init_array_syr2k(n, m, &alpha, &beta, POLYBENCH_ARRAY(C), POLYBENCH_ARRAY(A),
                   POLYBENCH_ARRAY(B));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_syr2k(n, m, alpha, beta, POLYBENCH_ARRAY(C), POLYBENCH_ARRAY(A),
               POLYBENCH_ARRAY(B));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array_syr2k(n, POLYBENCH_ARRAY(C)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(C);
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(B);

  return 0;
}
