cmake_minimum_required(VERSION 3.25)
project(turboaccelerated_rainbow_tables C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(turboaccelerated-rainbow-tables)

# OpenSSL
link_libraries(ssl)
link_libraries(crypto)

add_executable(turboaccelerated_rainbow_tables
        turboaccelerated-rainbow-tables/main.c
        turboaccelerated-rainbow-tables/md5_calc.c
        turboaccelerated-rainbow-tables/md5_calc.h)
