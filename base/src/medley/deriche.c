#include "medley/deriche.h"
#include "polybench.h"
#include <stdio.h>

void init_array_deriche(int w, int h, DATA_TYPE *alpha,
                        DATA_TYPE POLYBENCH_2D(imgIn, W, H, w, h),
                        DATA_TYPE POLYBENCH_2D(imgOut, W, H, w, h)) {
  int i, j;

  *alpha = 0.25; // parameter of the filter

  // input should be between 0 and 1 (grayscale image pixel)
  for (i = 0; i < w; i++)
    for (j = 0; j < h; j++)
      imgIn[i][j] = (DATA_TYPE)((313 * i + 991 * j) % 65536) / 65535.0f;
}

void print_array_deriche(int w, int h,
                         DATA_TYPE POLYBENCH_2D(imgOut, W, H, w, h)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("imgOut");
  for (i = 0; i < w; i++)
    for (j = 0; j < h; j++) {
      if ((i * h + j) % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, imgOut[i][j]);
    }
  POLYBENCH_DUMP_END("imgOut");
  POLYBENCH_DUMP_FINISH;
}
