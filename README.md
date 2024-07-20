# Turboaccelerated-rainbow-tables

A proof-of-concept application generating rainbow tables for MD5 hash function written in C.

##### Dependencies
- OpenSSL (*libssl* and *libcrypto*)
- GNU Multiple Precision Arithmetic Library GMP (*libgmp*)
- CMocka (*libcmocka*; only necessary if you need to compile tests)

#### How to build
Build from top of the repository tree.

Release:
> cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=make -DCMAKE_C_COMPILER=gcc -G "Unix Makefiles" -S . -B ./cmake-build-main

> cmake --build ./cmake-build-main --target trb -j 8 

Debug:
> cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=make -DCMAKE_C_COMPILER=gcc -DTESTS=ON -G "Unix Makefiles" -S . -B ./cmake-build-debug

> cmake --build ./cmake-build-debug --target trb -j 8

Singletest (debug version compiling only one specific test):
> cmake -DCMAKE_BUILD_TYPE=SingleTest -DCMAKE_MAKE_PROGRAM=make -DCMAKE_C_COMPILER=gcc -DSINGLE_TEST=ON -G "Unix Makefiles" -S . -B ./cmake-build-singletest

> cmake --build ./cmake-build-singletest --target trb -j 8

##### Authors
- Konrad Dumin

###### Notes
- The program only works with data in either ASCII or UTF-8 encoding
- All tests were commenced on Linux; the program wasn't tested on other Unix systems
- All input files need to be newline-terminated
- You can choose to compile either one single test or the whole test suite using switches in CMakeLists.txt
- In case of single test compilation, you may need to create *cmocka_main_single_test.c* yourself by copying the contents of *cmoccka_main.c* and filling main() with a single test of your choice
