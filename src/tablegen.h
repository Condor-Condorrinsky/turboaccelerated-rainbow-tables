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
 * endrslt_len - length of the buffer we are writing to
 * iterations - how many links of chain to generate, current maximum is equal to the sizeof REDUCTION_PATTERN_VALUES
 */
void generate_chain(const char* passwd, unsigned char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations);

/*
 * A wrapper for compute_md5 function; for more info see md5calc.h
 */
void hash(const char* input, unsigned char* digest, unsigned int digest_len);

/*
 * A wrapper for reduce function; for more info see reduction.h
 */
void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLEGEN_H
