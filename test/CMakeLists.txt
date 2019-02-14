add_executable(matrix_test_app
    backtrace.hpp
    backtrace.cpp
    test_main.cpp
	matrix_test.cpp)

target_link_libraries(matrix_test_app
    matrix
	libgtest
	libgmock
    )

add_test(NAME matrix_test
	COMMAND matrix_test_app)

#add_test(NAME matrix_test_gdb
#	COMMAND gdb --args matrix_test_app)

