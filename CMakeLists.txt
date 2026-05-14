cmake_minimum_required(VERSION 3.22)
project(PolyBench-C LANGUAGES C)

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
    include(cmake/AddPolyBenchLibrary.cmake)
    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_library(${NAME}_lib KERNEL ${NAME})
        target_compile_definitions(${NAME}_lib PUBLIC POLYBENCH_TIME)
    endforeach()

    include(cmake/AddPolyBenchExecutable.cmake)
    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_executable(${NAME} KERNEL ${NAME})
        target_link_libraries(${NAME} ${NAME}_lib)
    endforeach()
endif()
