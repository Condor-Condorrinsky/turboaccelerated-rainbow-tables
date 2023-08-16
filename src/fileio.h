#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H
#define TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H

#define IO_BUFF_SIZE                    65536
#define IO_EXIT_FAILURE                 (-1)
// 24 characters + null terminator
#define MAX_PASS_LENGTH                 25
#define MAX_LINE_WRITE_LENGTH           128

#define RAINBOW_TABLE_SEPARATOR         " -> "

long get_file_size(FILE * file);

int count_lines(FILE* file);

#endif //TURBOACCELERATED_RAINBOW_TABLES_FILEIO_H
