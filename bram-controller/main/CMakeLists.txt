file(GLOB bram_controller_SRC
        "commands/program_command.hpp"
        "commands/command_factory.hpp"
        "commands/command_factory.cpp"
        "commands/clear/clear_slient_command.hpp"
        "commands/clear/clear_verbose_command.hpp"
        "commands/read/read_command.hpp"
        "commands/read/read_silent_command.hpp"
        "commands/read/read_command_factory.hpp"
        "commands/read/read_verbose_command.hpp"
        "commands/write/write_command.hpp"
        "commands/write/write_command_factory.hpp"
        "commands/write/write_silent_command.hpp"
        "commands/write/write_verbose_command.hpp"
        "commands/error_code.hpp"
        "commands/help/help_verbose_command.hpp"
        "commands/help/help_silent_command.hpp"
        "commands/clear/clear_command.hpp"
        "base64/base_64.cpp"
        "base64/base_64.hpp"
        "utils/configuration_loader.h"
        "commands/clear/clear_command_factory.hpp"
        "exceptions/memory_exception.hpp"
        "utils/hex_argument_reader.hpp"
        "commands/write/write_program_memory_command.hpp"
        "commands/write/performance_check_read_command.hpp"
        "commands/write/write_silent_memcpy_command.hpp"
        "commands/write/write_silent_memcpy_custom_command.hpp.hpp"
        "commands/write/read_program_memory_command.hpp"
        "../program_settings.h"
        "utils/memcpy_custom.h"
        "utils/memcpy_custom.c"
        )

add_executable(bram_controller bram_controller.cpp ${bram_controller_SRC})

add_library(bram_controller_lib
        ${bram_controller_SRC})

target_include_directories(bram_controller_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})