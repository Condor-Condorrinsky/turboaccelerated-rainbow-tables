#include <string.h>
#include <gmp.h>
#include "md5calc.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H
#define TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H

// 16 characters + null terminator
#define MAX_REDUCED_PASS_LENGTH                  17

void R(const unsigned char* digest, char* output, unsigned int output_len, char* reduction_iteration);

/*
 * Reduction function used to convert hashes into possible plaintext passwords for rainbow table hash chain generation.
 * Accepts a reduction pattern in the form of "A_B_C_D_E_F..." where letters are numbers from 0 to 15 inclusive.
 * These numbers represent which bytes od the hash are to be taken into account for generation - order matters!
 * Function supports patterns of length from "A" to "A_B_C_D_E_F_G_H_I_J_K_L_M_N_O_P" (up to 16 numbers, since MD5
 * consists of 16 bytes).
 *
 * digest - hash (in raw form, not string) to be reduced into another password
 * output - buffer to store the output of operation; minimum 17 bytes of length
 * reduction_pattern - string in the form described earlier
 * output_len - length of output array, must be at least MAX_REDUCED_PASS_LENGTH
 * reduced_pass_len - length of the reduced password we are generating
 */
void reduce(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len,
            unsigned int reduced_pass_len);

/*
 * A common idiomatic use of strncpy wrapped in a convenient function
 *
 * Args and return value the same as in original strncpy function
 */
char* safer_strncpy(char* dest, const char* src, size_t n);

/*
 * Splits the pattern string literal by '_' into unsigned char array
 * WARNING: destroys the original string (strtok_r is used on input)
 *
 * input - pattern to split
 * result - unsigned char array to write results to
 * result_len - length of result array, minimum 16 chars
 */
int split_by_underscores(char* input, unsigned char* result, unsigned int result_len);

/*
 * A helper function converting a small number (1 byte of hash) to a non-white printable ASCII character,
 * excluding '|'
 *
 * in - byte of hash to be converted
 *
 * Returns a char with a value from 33 to 126 excluding 124
 */
char unsigned_char_to_ascii(unsigned char in);

/*
 * A helper function converting a small number (1 byte of hash) to a small letter of English alphabet
 *
 * in - byte of hash to be converted
 *
 * Returns a char with a value from 97 to 122 - ascii values for small letters of English alphabet
 */
char unsigned_char_to_small_letter(unsigned char in);

#endif //TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H
