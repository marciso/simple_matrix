add_executable(matrix_test_app
	matrix_test.cpp)

target_link_libraries(matrix_test_app
    matrix
	libgmock_main
	libgtest
	libgmock
    )

add_test(NAME matrix_test
	COMMAND matrix_test_app)

