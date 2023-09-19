#include <string.h>
#include <gmp.h>
#include "md5calc.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H
#define TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H

// 16 characters + null terminator
#define MAX_REDUCED_PASS_LENGTH                  17

const static char* SIX_LETTER_PASSES_SMALL_LETTERS_SET_SIZE_STR = "308915776";
const static char* EIGHT_DIGIT_PINS_SET_SIZE_STR = "100000000";

void R(const unsigned char* digest, char* output, unsigned int output_len, const char* reduction_iteration);

void encode(char* number, unsigned int desired_len, char* output_buf, unsigned int output_len);

/*
 * https://stackoverflow.com/questions/276827/string-padding-in-c
 */
void pad_str_leading_zeroes(char* number, unsigned int desired_len, char* output_buf, unsigned int output_len);

/*
 * A common idiomatic use of strncpy wrapped in a convenient function
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
