set(libfoo_SRCS commands/read/read_command.hpp commands/read/read_command_verbose.hpp commands/read/read_command_application.hpp commands/write/write_command.hpp commands/write/write_command_verbose.hpp commands/write/write_command_application.hpp commands/command_factory.hpp commands/read/read_command_factory.hpp commands/write/write_command_factory.hpp commands/program_command.hpp commands/command_factory.cpp)


# Declare the library
add_library(libfoo STATIC
        ${libfoo_SRCS}
        )

# Specify here the include directories exported
# by this library
target_include_directories(libfoo PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )