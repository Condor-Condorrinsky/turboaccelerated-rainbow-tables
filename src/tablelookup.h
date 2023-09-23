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
 * looked_hash - C string representing MD5 looked_hash we are looking for, in the form of
 * "0xABCDEF0123456789ABCDEF0123456789"
 */
int lookup(FILE* rainbow_file, const char* looked_hash);

/*
 * Extracts all reduced values from pre-generated table and places the result
 * in given buffer. The extracted values are newline-separated. Doesn't take a length
 * argument because length of the table may vary wildly - it is caller's responsibility
 * to ensure proper size of the buffer pointed by extracted_table
 *
 * complete_table - pre-generated rainbow table stored in a C string
 * extracted table - buffer to store the extracted reduced hashes, output is newline-separated
 * and null-terminated
 */
void extract_hashed_vals(char* complete_table, PassHashChain** extracted_table);

void line_to_PassHashChain(char* line, PassHashChain* c);

int find_hash(PassHashChain** table, unsigned int entries, const char* looked_hash);

int find_hash_in_chain(const PassHashChain* c, const char* hash_to_find);

int str_to_uppercase(const char* input, char* output, unsigned int output_len);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
