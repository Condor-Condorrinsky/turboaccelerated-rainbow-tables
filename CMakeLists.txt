cmake_minimum_required(VERSION 3.25)
project(turboaccelerated_rainbow_tables)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

OPTION(TESTS "Compile tests" OFF)

if(TESTS)
    add_executable(trb
            # Test files
            tst/fileio_test.cpp
            tst/md5calc_test.cpp
            tst/reduction_test.cpp
            tst/tablegen_test.cpp
            tst/tablelookup_test.cpp
            # Src, without main
            src/md5calc.c
            src/md5calc.h
            src/PassHashChain.c
            src/PassHashChain.h
            src/reduction.c
            src/reduction.h
            src/tablegen.c
            src/tablegen.h
            src/patternenum.h
            src/fileio.c
            src/fileio.h
            src/tablelookup.c
            src/tablelookup.h)
    target_include_directories(trb
            PUBLIC src
            PUBLIC tst
    )

    enable_testing()

    # GTest (Google Test)
    set(GTest_DIR .)
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(trb
            GTest::gtest
            GTest::gtest_main)
else ()
    add_executable(trb
            src/main.c
            src/md5calc.c
            src/md5calc.h
            src/PassHashChain.c
            src/PassHashChain.h
            src/reduction.c
            src/reduction.h
            src/tablegen.c
            src/tablegen.h
            src/patternenum.h
            src/fileio.c
            src/fileio.h
            src/tablelookup.c
            src/tablelookup.h)
    target_include_directories(trb
            PUBLIC src
    )
endif()

# OpenSSL
set(ssl_DIR .)
set(crypto_DIR .)
find_package(ssl CONFIG REQUIRED)
find_package(crypto CONFIG REQUIRED)
target_link_libraries(trb
        ssl)
target_link_libraries(trb
        crypto)
# GMP - GNU Multiple Precision Arithmetic Library
set(gmp_DIR .)
find_package(gmp CONFIG REQUIRED)
target_link_libraries(trb
        gmp)
