set(Main_SRCS
        bram_controller.cpp
        )

add_executable(bram_controller
        ${Main_SRCS}
        )

# Specify here the libraries this program depends on
target_link_libraries(bram_controller
        libfoo
        )

install(TARGETS bram_controller DESTINATION bin)
