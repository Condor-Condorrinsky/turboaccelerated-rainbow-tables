#include <string.h>
#include <gmp.h>
#include "charsets.h"
#include "md5calc.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H
#define TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H

// 64 characters + null terminator
#define MAX_REDUCED_PASS_LENGTH                  65
// For a 64 character password with 93 possible ascii vals each we have ~ 9*10^167 combinations,
// therefore a buffer of this size should be sufficient for all the digits of that number
#define SET_SIZE_BUFFER                          1024

/*
 * https://crypto.stackexchange.com/questions/37832/how-to-create-reduction-functions-in-rainbow-tables
 *
 * Main reduction function, reduces given hash to a new plaintext.
 *
 * digest - raw hash generated by compute_md5()
 * output - output buffer to store the result
 * output_len - length of the output buffer
 * reduction_iteration - constant string representing a small number used in reduction; allows to generate a whole
 * family of related reduction functions
 * set_size - C string representing a number - set size for given charset and password length for GMP library
 * e.g. "1000" for 4-letter passwords containing only digits; to be calculated by calc_R_set_size()
 * pass_len - length of the reduced password
 */
void R(const unsigned char* digest, char* output, unsigned int output_len, const char* reduction_iteration,
       const char* set_size, unsigned int pass_len);

void calc_R_set_size(unsigned int pass_len, int mode, char* output, unsigned int output_len);

/*
 * https://stackoverflow.com/questions/276827/string-padding-in-c
 *
 * Pads the given string with leading zeroes to the desired length
 *
 * number - number represented as string to pad
 * desired_len - length we want to pad string to; bigger than or equal to strlen(number)
 * output_buf - buffer to store the result of the operation to; can be the same as input buffer (number param)
 * output_len - length of the output buffer
 */
void pad_str_leading_zeroes(char* number, unsigned int desired_len, char* output_buf, unsigned int output_len);

/*
 * A common idiomatic usage of strncpy wrapped in a convenient function
 *
 * Args and return value the same as in original strncpy function
 */
char* safer_strncpy(char* dest, const char* src, size_t n);

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
