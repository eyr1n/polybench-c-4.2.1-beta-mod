#include "stencils/fdtd-2d.h"
#include "polybench.h"
#include <stdio.h>

void init_array_fdtd_2d(int tmax, int nx, int ny,
                        DATA_TYPE POLYBENCH_2D(ex, NX, NY, nx, ny),
                        DATA_TYPE POLYBENCH_2D(ey, NX, NY, nx, ny),
                        DATA_TYPE POLYBENCH_2D(hz, NX, NY, nx, ny),
                        DATA_TYPE POLYBENCH_1D(_fict_, TMAX, tmax)) {
  int i, j;

  for (i = 0; i < tmax; i++)
    _fict_[i] = (DATA_TYPE)i;
  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++) {
      ex[i][j] = ((DATA_TYPE)i * (j + 1)) / nx;
      ey[i][j] = ((DATA_TYPE)i * (j + 2)) / ny;
      hz[i][j] = ((DATA_TYPE)i * (j + 3)) / nx;
    }
}

void print_array_fdtd_2d(int nx, int ny,
                         DATA_TYPE POLYBENCH_2D(ex, NX, NY, nx, ny),
                         DATA_TYPE POLYBENCH_2D(ey, NX, NY, nx, ny),
                         DATA_TYPE POLYBENCH_2D(hz, NX, NY, nx, ny)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("ex");
  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++) {
      if ((i * nx + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, ex[i][j]);
    }
  POLYBENCH_DUMP_END("ex");
  POLYBENCH_DUMP_FINISH;

  POLYBENCH_DUMP_BEGIN("ey");
  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++) {
      if ((i * nx + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, ey[i][j]);
    }
  POLYBENCH_DUMP_END("ey");

  POLYBENCH_DUMP_BEGIN("hz");
  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++) {
      if ((i * nx + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, hz[i][j]);
    }
  POLYBENCH_DUMP_END("hz");
}

void kernel_fdtd_2d(int tmax, int nx, int ny,
                    DATA_TYPE POLYBENCH_2D(ex, NX, NY, nx, ny),
                    DATA_TYPE POLYBENCH_2D(ey, NX, NY, nx, ny),
                    DATA_TYPE POLYBENCH_2D(hz, NX, NY, nx, ny),
                    DATA_TYPE POLYBENCH_1D(_fict_, TMAX, tmax)) {
  int t, i, j;

#pragma scop

  for (t = 0; t < _PB_TMAX; t++) {
    for (j = 0; j < _PB_NY; j++)
      ey[0][j] = _fict_[t];
    for (i = 1; i < _PB_NX; i++)
      for (j = 0; j < _PB_NY; j++)
        ey[i][j] = ey[i][j] - SCALAR_VAL(0.5) * (hz[i][j] - hz[i - 1][j]);
    for (i = 0; i < _PB_NX; i++)
      for (j = 1; j < _PB_NY; j++)
        ex[i][j] = ex[i][j] - SCALAR_VAL(0.5) * (hz[i][j] - hz[i][j - 1]);
    for (i = 0; i < _PB_NX - 1; i++)
      for (j = 0; j < _PB_NY - 1; j++)
        hz[i][j] = hz[i][j] - SCALAR_VAL(0.7) * (ex[i][j + 1] - ex[i][j] +
                                                 ey[i + 1][j] - ey[i][j]);
  }

#pragma endscop
}
