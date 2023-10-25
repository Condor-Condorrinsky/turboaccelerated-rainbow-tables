#include "fileio.h"

int load_file(FILE* file, char* buffer, unsigned int buffer_len){
    int bytes_read = 0;
    char* end = buffer;

    if (buffer_len < get_file_size(file)){
        fprintf(stderr, "Too small buffer to read into\n");
        return IO_EXIT_FAILURE;
    }

    rewind(file);

    for(;;) {
        size_t res = fread(buffer, sizeof(char), IO_BUFF_SIZE, file);
        bytes_read += (int) res;
        if (ferror(file)) {
            fprintf(stderr, "IO generic error\n");
            return IO_EXIT_FAILURE;
        }
        if (res == 0)
            break;

        buffer += IO_BUFF_SIZE;
    }

    end += bytes_read;
    *end = '\0';

    return bytes_read;
}

void write_metadata(FILE* file, TableMetadata* t){
    fprintf(file, "Chain length:%d\n", t->chain_len);
    switch (t->charset) {
        case DIGITS:
            fprintf(file, "Charset%s%s\n", RAINBOW_TABLE_META_SEPARATOR, CHARSETS_STR[DIGITS]);
            break;
        case ALPHANUMERIC:
            fprintf(file, "Charset%s%s\n", RAINBOW_TABLE_META_SEPARATOR, CHARSETS_STR[ALPHANUMERIC]);
            break;
        case ASCII_PRINTABLE:
            fprintf(file, "Charset%s%s\n", RAINBOW_TABLE_META_SEPARATOR, CHARSETS_STR[ASCII_PRINTABLE]);
            break;
        default:
            fprintf(file, "Charset%s%s\n", RAINBOW_TABLE_META_SEPARATOR,
                    "WARNING! CHARSET UNKNOWN, THE TABLE IS MALFORMED");
            break;
    }
}

void write_line(FILE* file, const char* pass, const char* reduced){
    fprintf(file, "%s%s%s\n", pass, RAINBOW_TABLE_SEPARATOR, reduced);
}

long get_file_size(FILE* file){
    struct stat s;
    int fd;

    if ((fd = fileno(file)) < 0){
        fprintf(stderr, "Couldn't open file descriptor for size estimation\n");
        return -1;
    }
    if ((fstat(fd, &s))){
        fprintf(stderr, "Couldn't get file info for size estimation\n");
        return -2;
    }

    return s.st_size;
}

unsigned int count_lines(FILE* file) {
    char* buf = malloc(sizeof(char) * IO_BUFF_SIZE);
    unsigned int counter = 0;

    rewind(file);

    for(;;) {
        size_t res = fread(buf, sizeof(char), IO_BUFF_SIZE, file);
        if (ferror(file)){
            fprintf(stderr, "Error encountered when counting lines\n");
            free(buf);
            return IO_EXIT_FAILURE;
        }

        for (int i = 0; i < res; i++)
            if (buf[i] == NEWLINE_CHAR)
                counter++;

        if (res == 0)
            break;
    }
    free(buf);
    return counter;
}
