cmake_minimum_required(VERSION 3.22)
project(PolyBench LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
if(NOT PROJECT_IS_TOP_LEVEL)
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)
endif()

include(PolyBench)

option(POLYBENCH_BUILD_EXAMPLES "" OFF)

set(POLYBENCH_BENCHMARKS
    correlation
    covariance
    gemm
    gemver
    gesummv
    symm
    syr2k
    syrk
    trmm
    two_mm
    three_mm
    atax
    bicg
    doitgen
    mvt
    cholesky
    durbin
    gramschmidt
    lu
    ludcmp
    trisolv
    deriche
    floyd_warshall
    nussinov
    adi
    fdtd_2d
    heat_3d
    jacobi_1d
    jacobi_2d
    seidel_2d
)

if(POLYBENCH_BUILD_EXAMPLES)
    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_library(${NAME}_lib KERNEL ${NAME})
        target_compile_definitions(${NAME}_lib PUBLIC POLYBENCH_TIME)
    endforeach()

    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_executable(${NAME} KERNEL ${NAME})
        target_link_libraries(${NAME} ${NAME}_lib)
    endforeach()
endif()
