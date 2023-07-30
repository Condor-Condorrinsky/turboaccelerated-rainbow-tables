#include "stdint.h"
#include "openssl/types.h"
#include "openssl/evp.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
#define TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H

#define MD5_DIGEST_LENGTH           16
#define EVP_DIGEST_UPDATE_NUM_BYTES 64

/*
 * Computes the MD5 hash of the given string
 *
 * input - the string to be hashed
 * digest - buffer where the end result will be stored, MUST be at least 16 chars long
 *
 * Returns the number of bytes written - the length of the digest
 */
unsigned int compute_md5(const char* input, unsigned char* digest);

/*
 * razz's answer
 * https://stackoverflow.com/questions/6357031/how-do-you-convert-a-byte-array-to-a-hexadecimal-string-in-c
 *
 * Similar to print_hash, but converts to null-terminated string in memory instead of
 * directly printing to stdout.
 *
 * input - md5 digest
 * output - buffer to write to; for MD5 it MUST be at least 2 * MD5_DIGEST_LENGTH + 1 long
 */
void convert_to_string(const unsigned char* input, char* output);

/*
 * Prints created hash to stdout
 * input - buffer with computed hash
 */
void print_hash(const unsigned char* input);

#endif //TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
