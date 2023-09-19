#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H
#define TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H

#define IO_BUFF_SIZE                    65536
#define IO_EXIT_FAILURE                 (-1)

#define RAINBOW_TABLE_SEPARATOR         "|"
#define NEWLINE_STRING                  "\n"
#define NEWLINE_CHAR                    '\n'

/*
 * Loads whole password database file into memory.
 * Does not terminate the data loaded to buffer with NULL.
 *
 * file - FILE handler to read file
 * buffer - buffer to store the contents into
 * buffer_len - length of the provided buffer
 *
 * Returns number of bytes read from the given FILE
 */
int load_file(FILE* file, char* buffer, unsigned int buffer_len);

/*
 * Writes a single line to a given plaintext in the format of (without quotes):
 * "*pass*|*final_hash*\n"
 * Designed to generate a nicely-looking rainbow table
 *
 * file - FILE handler to read file
 * pass - password which eventually reduces to reduced parameter
 * reduced - hash after whole chain generation
 */
void write_line(FILE* file, const char* pass, const char* reduced);

/*
 * Counts chars in given plaintext file
 *
 * file - FILE handler to read file
 *
 * Returns number of chars in file, negative value in case of an error
 */
long get_file_size(FILE * file);

/*
 * Counts non-empty lines in given plaintext file. All input files are expected to be newline-terminated.
 *
 * file - FILE handler to read file
 *
 * Returns number of line breaks decremented by 1 in file, negative value in case of an error
 */
unsigned int count_lines(FILE* file);

#endif //TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H
