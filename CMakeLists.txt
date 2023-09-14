cmake_minimum_required(VERSION 3.25)
project(turboaccelerated_rainbow_tables C)

set(CMAKE_C_STANDARD 11)

OPTION(TESTS "Compile tests" OFF)

if(TESTS)
    add_executable(trb
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
            src/tablelookup.h
            # CMocka tests
            tst/cmocka_main.c
            tst/fileio_test.c
            tst/md5calc_test.c
            tst/reduction_test.c
            tst/tablegen_test.c
            tst/tablelookup_test.c
    )
    target_include_directories(trb
            PUBLIC src
            PUBLIC tst
    )

    enable_testing()

    # CMocka - C Unit testing framework
    set(cmocka_DIR .)
    find_package(cmocka CONFIG REQUIRED)
    target_link_libraries(trb
            cmocka)
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
find_package(ssl CONFIG REQUIRED)
target_link_libraries(trb
        ssl)

# OpenSSL Crypto
set(crypto_DIR .)
find_package(crypto CONFIG REQUIRED)
target_link_libraries(trb
        crypto)

# GMP - GNU Multiple Precision Arithmetic Library
set(gmp_DIR .)
find_package(gmp CONFIG REQUIRED)
target_link_libraries(trb
        gmp)
