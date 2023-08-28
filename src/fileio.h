#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#ifndef TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H
#define TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H

#define IO_BUFF_SIZE                    65536
#define IO_EXIT_FAILURE                 (-1)
// 32 characters + null terminator
#define MAX_REDUCED_PASS_LENGTH         33

#define RAINBOW_TABLE_SEPARATOR         "|"

/*
 * Loads whole password database file into memory
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
 * "*pass* -> *reduced*\n"
 * Designed to generate a nicely-looking rainbow table
 *
 * file - FILE handler to read file
 * pass - password which eventually reduces to reduced parameter
 * reduced - pass after whole chain generation
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
 * Counts line in given plaintext file
 *
 * file - FILE handler to read file
 *
 * Returns number of line breaks in file, negative value in case of an error
 */
int count_lines(FILE* file);

#endif //TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H
