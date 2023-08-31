#include <string.h>
#include "fileio.h"
#include "patternenum.h"
#include "reduction.h"
#include "tablegen.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
#define TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H

#define LOOKUP_DELIMS                             "|\n"

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
void extract_reduced_vals(char* complete_table, char* extracted_table);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLELOOKUP_H
