#include <string.h>
#include "fileio.h"
#include "patternenum.h"
#include "reduction.h"
#include "tablegen.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
#define TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H

#define HASH_FOUND                                  0
#define HASH_NOT_FOUND                              1

#define LOOKUP_DELIMS                           "|\n"

/*
 * Performs hash look up in a given rainbow table
 *
 * rainbow_file - a file descriptor with pre-generated rainbow table (read-only)
 * hash - C string representing MD5 hash we are looking for, in the form of
 * "0xABCDEF0123456789ABCDEF0123456789"
 */
void lookup(FILE* rainbow_file, const char* hash);

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
void extract_hashed_vals(char* complete_table, char* extracted_table);

/*
 * Looks for a given hash in a single chain in the rainbow table
 *
 * loaded_hash - hash loaded form rainbow table which we are comparing against
 * md5hash - hash we are trying to find in the chain
 *
 * Returns HASH_FOUND on success, HASH_NOT_FOUND otherwise
 */
int perform_chain_lookup(const char* loaded_hash, const char* md5hash);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
