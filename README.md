# Turboaccelerated-rainbow-tables

A proof-of-concept application generating rainbow tables for MD5 hash function written in C and hardware-accelerated using Alveo U50.

##### Dependencies
- OpenSSL (*libssl* and *libcrypto*)
- GNU Multiple Precision Arithmetic Library GMP (*libgmp*)
- CMocka (*libcmocka*; only necessary if you need to compile tests)

##### Authors
- Konrad Dumin

###### Notes
- The program only works with data in either ASCII or UTF-8 encoding
- All input files need to be newline-terminated
- You can choose to compile either one single test or the whole test suite using switches in CMakeLists.txt
- In case of single test compilation, you may need to create *cmocka_main_single_test.c* yourself by copying the contents of *cmoccka_main.c* and filling main() with a single test of your choice
