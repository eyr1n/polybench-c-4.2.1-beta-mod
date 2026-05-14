#include "medley/floyd-warshall.h"
#include "polybench.h"
#include <stdio.h>

void init_array_floyd_warshall(int n,
                               DATA_TYPE POLYBENCH_2D(path, N, N, n, n)) {
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      path[i][j] = i * j % 7 + 1;
      if ((i + j) % 13 == 0 || (i + j) % 7 == 0 || (i + j) % 11 == 0)
        path[i][j] = 999;
    }
}

void print_array_floyd_warshall(int n,
                                DATA_TYPE POLYBENCH_2D(path, N, N, n, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("path");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if ((i * n + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, path[i][j]);
    }
  POLYBENCH_DUMP_END("path");
  POLYBENCH_DUMP_FINISH;
}

void kernel_floyd_warshall(int n, DATA_TYPE POLYBENCH_2D(path, N, N, n, n)) {
  int i, j, k;

#pragma scop
  for (k = 0; k < _PB_N; k++) {
    for (i = 0; i < _PB_N; i++)
      for (j = 0; j < _PB_N; j++)
        path[i][j] = path[i][j] < path[i][k] + path[k][j]
                         ? path[i][j]
                         : path[i][k] + path[k][j];
  }
#pragma endscop
}
