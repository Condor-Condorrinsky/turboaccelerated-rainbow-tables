#include "fileio.h"
#include "patternenum.h"
#include "reduction.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_TABLEGEN_H
#define TURBOACCELERATED_RAINBOW_TABLES_TABLEGEN_H

/*
 * Main function generating whole rainbow table from given input file with exemplary passwords
 * (new line separated) and storing the result in another file
 *
 * in - FILE handler for input file
 * out - FILE handler for output file
 */
void generate_rainbow_table(FILE* in, FILE* out);

/*
 * Function generating a single complete rainbow chain stemming from one password
 *
 * passwd - C string to generate chain from
 * endrslt - buffer to write a final reduced hash to
 * passwd_len - length of passwd string, without null terminator
 * endrslt_len - length of the buffer we are writing to
 * iterations - how many links of chain to generate, current maximum is equal to the sizeof REDUCTION_PATTERN_VALUES
 */
void generate_chain(const char* passwd, unsigned char* endrslt, unsigned int passwd_len, unsigned int endrslt_len,
                    unsigned int iterations);

/*
 * A helper function for generate_chain function, providing the operation of hashing the input and immediately
 * reducing it
 *
 * input - password (C string) to be hashed and reduced
 * output - buffer to store the reduced hash
 * input_len - length of the input, without null terminator
 * output_len - length of the output buffer
 * reduction_pattern - pattern to reduce the hash with; for more info see reduce function in reduction.h
 */
void hash_and_reduce(const char* input, char* output, unsigned int input_len, unsigned int output_len,
                     const char* reduction_pattern);

/*
 * A helper function for reducing a hash and then hashing it again afterwards.
 *
 * input - hash to be reduced and hashed
 * output - buffer to store the result of the operation
 * output_len - size of the output buffer, 16 at minimum
 * reduction_pattern - pattern to reduce the hash with; for more info see reduce function in reduction.h
 */
void reduce_and_hash(const unsigned char input[MD5_DIGEST_LENGTH], unsigned char output[MD5_DIGEST_LENGTH],
                     unsigned int output_len, const char* reduction_pattern);

/*
 * A wrapper for compute_md5 function; for more info see md5calc.h
 */
void hash(const char* input, unsigned char* digest, unsigned int input_len, unsigned int digest_len);

/*
 * A wrapper for reduce function; for more info see reduction.h
 */
void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLEGEN_H
