cmake_minimum_required(VERSION 3.25)
project(turboaccelerated_rainbow_tables)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

OPTION(TESTS "Compile tests" OFF)

if(TESTS)
    include_directories(tst)
    add_executable(turboaccelerated_rainbow_tables
            # Test files
            # tst/gtest_main.cpp
            tst/md5_calc_test.cpp
            # Src, without main
            src/md5_calc.c
            src/md5_calc.h)

    enable_testing()
    set(GTest_DIR .)
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(turboaccelerated_rainbow_tables
            GTest::gtest
            GTest::gtest_main)
else ()
    add_executable(turboaccelerated_rainbow_tables
            src/main.c
            src/md5_calc.c
            src/md5_calc.h)
endif()

# OpenSSL
set(ssl_DIR .)
set(crypto_DIR .)
find_package(ssl CONFIG REQUIRED)
find_package(crypto CONFIG REQUIRED)
target_link_libraries(turboaccelerated_rainbow_tables
        ssl)
target_link_libraries(turboaccelerated_rainbow_tables
        crypto)
