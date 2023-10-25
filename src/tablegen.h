#include "fileio.h"
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
void generate_rainbow_table(FILE* in, FILE* out, TableMetadata* meta);

/*
 * Function generating a single complete rainbow chain stemming from one password
 *
 * passwd - C string to generate chain from
 * endrslt - buffer to write a final reduced hash to
 * endrslt_len - length of the buffer we are writing to
 * iterations - how many links of chain to generate, current maximum is equal to REDUCTION_PATTERNS_SIZE
 * set_size - size of the set we are reducing passwords to; calculated using calc_set_size()
 */
void generate_chain(const char* passwd, char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations, const char* set_size, int mode);

/*
 * Custom itoa() function. Converts given integer i to a string. Based on snprintf().
 *
 * i - integer to convert
 * buf - buffer to write result to
 * buf_len - buf length
 */
void iter_itoa(int i, char* buf, unsigned int buf_len);

/*
 * A wrapper for compute_md5 function; for more info see md5calc.h
 */
void hash(const char* input, unsigned char* digest, unsigned int digest_len);

/*
 * A wrapper for reduce function; for more info see reduction.h
 */
void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len,
                 const char* set_size, unsigned int reduced_pass_len, int mode);

/*
 * A wrapper for calc_R_set_size function; for more info see reduction.h
 */
void calc_set_size(unsigned int pass_len, int mode, char* output, unsigned int output_len);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLEGEN_H
