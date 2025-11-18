configure_file(
    "config.hpp.in"
    #path to build dir
    "${CMAKE_BINARY_DIR}/config/include/config.hpp" ESCAPE_QUOTES
)