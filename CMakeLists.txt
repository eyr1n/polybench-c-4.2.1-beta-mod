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
    include(cmake/AddPolyBenchBase.cmake)
    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_base(${NAME}_base NAME ${NAME})
        target_compile_definitions(${NAME}_base PUBLIC POLYBENCH_TIME)
    endforeach()

    include(cmake/AddPolyBenchKernel.cmake)
    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_kernel(${NAME}_kernel
            NAME ${NAME}
            BASE ${NAME}_base
        )
    endforeach()

    include(cmake/AddPolyBenchExecutable.cmake)
    foreach(NAME IN LISTS POLYBENCH_BENCHMARKS)
        add_polybench_executable(${NAME}
            NAME ${NAME}
            KERNEL ${NAME}_kernel
        )
    endforeach()
endif()
