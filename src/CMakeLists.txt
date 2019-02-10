
add_library(matrix STATIC
    matrix.hpp
    matrix.cpp
)

target_include_directories(matrix
	INTERFACE .)

add_executable(matrix_app
    main.cpp
)

target_link_libraries(matrix_app
    matrix)
