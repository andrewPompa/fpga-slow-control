add_executable(
        performance_test
        performance_test.cpp
        test_configuration.h
        test_statistics.hpp
        tests/read_test.hpp
        tests/write_test.hpp
        tests/read_write_test.hpp
        tests/processor_read_test.hpp
        tests/processor_read_write_test.hpp
        tests/processor_write_test.hpp
        tests/write_memcpy_test.hpp
        tests/write_memcpy_custom_test.hpp
)
target_link_libraries(performance_test bram_controller_lib)