# Turboaccelerated-rainbow-tables

A proof-of-concept application generating rainbow tables for MD5 hash function written in C and hardware-accelerated using Alveo U50.

##### Dependencies
- OpenSSL (*libssl* and *libcrypto*)
- GoogleTest (*libgtest*; only necessary if you need to compile tests)

##### Authors
- Konrad Dumin

###### Notes
- GoogleTest discourages usage of underscore in test suite names, hence inconsistent naming scheme in tests
- The program only works with data in either ASCII or UTF-8 encoding
- All input files need to be newline-terminated
