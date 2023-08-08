#include <stdint.h>
#include <stdlib.h>
#include <openssl/types.h>
#include <openssl/evp.h>

#ifndef TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
#define TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H

#define MD5_DIGEST_LENGTH           16

/*
 * Computes the MD5 hash of the given string
 *
 * input - the string to be hashed
 * digest - buffer where the end result will be stored, MUST be at least 16 chars long, it is NOT a null-terminated
 * C string
 * input_len - length of hashed string, without null terminator
 * digest_len - length of the buffer we are writing to, values of 15 or lower cause program to exit
 *
 * Returns the number of bytes written - the length of the digest
 */
unsigned int compute_md5(const char* input, unsigned char* digest, unsigned int input_len, unsigned int digest_len);

/*
 * razz's answer
 * https://stackoverflow.com/questions/6357031/how-do-you-convert-a-byte-array-to-a-hexadecimal-string-in-c
 *
 * Converts to C string and stores output to a buffer.
 *
 * input - md5 digest
 * output - buffer to write to
 * input_length - length of the digest buffer, mandatory to be equal to MD5_DIGEST_LENGTH = 16
 * output_len - length of the output buffer, for MD5 MUST be at least 2 * MD5_DIGEST_LENGTH + 1 long
 */
void convert_to_string(const unsigned char* input, char* output, unsigned int input_len, unsigned int output_len);

#endif //TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
