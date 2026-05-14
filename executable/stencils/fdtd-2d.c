#include "stencils/fdtd-2d.h"
#include "polybench.h"
#include <string.h>

int main(int argc, char **argv) {
  /* Retrieve problem size. */
  int tmax = TMAX;
  int nx = NX;
  int ny = NY;

  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(ex, DATA_TYPE, NX, NY, nx, ny);
  POLYBENCH_2D_ARRAY_DECL(ey, DATA_TYPE, NX, NY, nx, ny);
  POLYBENCH_2D_ARRAY_DECL(hz, DATA_TYPE, NX, NY, nx, ny);
  POLYBENCH_1D_ARRAY_DECL(_fict_, DATA_TYPE, TMAX, tmax);

  /* Initialize array(s). */
  init_array_fdtd_2d(tmax, nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey),
                     POLYBENCH_ARRAY(hz), POLYBENCH_ARRAY(_fict_));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_fdtd_2d(tmax, nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey),
                 POLYBENCH_ARRAY(hz), POLYBENCH_ARRAY(_fict_));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array_fdtd_2d(
      nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(ex);
  POLYBENCH_FREE_ARRAY(ey);
  POLYBENCH_FREE_ARRAY(hz);
  POLYBENCH_FREE_ARRAY(_fict_);

  return 0;
}
