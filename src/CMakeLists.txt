
add_library(matrix STATIC
    dummy.cpp
    simple_matrix.hpp
    transpose.hpp
    slice.hpp
    addition.hpp
    naive_multiplication.hpp
    scalar.hpp
    apply.hpp
)

target_include_directories(matrix
	INTERFACE .)

add_executable(matrix_app
    main.cpp
)

target_link_libraries(matrix_app
    matrix)
