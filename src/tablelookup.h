#include <string.h>
#include <ctype.h>
#include "fileio.h"
#include "PassHashChain.h"
#include "patternenum.h"
#include "reduction.h"
#include "tablegen.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
#define TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H

#define HASH_FOUND                                  0

// Found appropriate chain, but for some reason chain look up failed
#define HASH_NOT_FOUND                              1

// Hash is not present in the rainbow table
#define HASH_NOT_PRESENT                            2

/*
 * Performs looked_hash look up in a given rainbow table
 *
 * rainbow_file - a file descriptor with pre-generated rainbow table (read-only)
 * looked_hash - C string representing MD5 hash we are looking for, in the form of
 * "0xABCDEF0123456789ABCDEF0123456789"
 */
int lookup(FILE* rainbow_file, const char* looked_hash);

/*
 * Extracts all reduced values from pre-generated table and places the result
 * in given PassHashChain "array". It is caller's responsibility
 * to ensure proper size of the output table pointed to by extracted_table
 *
 * complete_table - pre-generated rainbow table stored in a C string
 * extracted table - array to store read table of PassHashChain structs
 */
void extract_hashed_vals(char* complete_table, PassHashChain** extracted_table);

/*
 * Helper function converting a single line of plaintext table into a PassHashChain struct.
 * PassHashChain c struct needs to be initialized before being passed to the function!
 *
 * line - C string representing single line of generated plaintext table
 * c - struct to write data to
 */
void line_to_PassHashChain(char* line, PassHashChain* c);

/*
 * The main function responsible for look up of the given hash in an extracted table
 *
 * table - table of password-hash chains extracted from a pre-generated file
 * entries - number of entries in the table
 * looked_hash - C string representing hash we are trying to break
 * set_size - string containing a number - set size
 * mode - DIGITS, ALPHANUMERIC or ASCII_PRINTABLE
 */
int find_hash(PassHashChain** table, unsigned int entries, const char* looked_hash, const char* set_size, int mode);

/*
 * Helper function testing whether the chain suspected by find_hash() to contain looked_hash
 * does indeed contain it.
 *
 * c - PassHashChain struct representing hash chain to test
 * hash_to_find - hash we are trying to break
 * set_size - string containing number - set size
 * mode - DIGITS, ALPHANUMERIC or ASCII PRINTABLE
 */
int find_hash_in_chain(const PassHashChain* c, const char* hash_to_find, const char* set_size, int mode);

/*
 * Small helper converting all letters in given C string to uppercase
 *
 * input - string to convert
 * output - buffer to write converted version to
 * output_len - length of the output buffer
 */
int str_to_uppercase(const char* input, char* output, unsigned int output_len);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
