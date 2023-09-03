#include "fileio.h"

int load_file(FILE* file, char* buffer, unsigned int buffer_len){
    int bytes_read = 0;
    char* end = buffer;

    if (buffer_len < get_file_size(file)){
        fprintf(stderr, "Too small buffer to read into");
        return IO_EXIT_FAILURE;
    }

    for(;;) {
        size_t res = fread(buffer, sizeof(char), IO_BUFF_SIZE, file);
        bytes_read += (int) res;
        if (ferror(file)) {
            fprintf(stderr, "IO generic error");
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

void write_line(FILE* file, const char* pass, const char* reduced){
    fprintf(file, "%s%s%s\n", pass, RAINBOW_TABLE_SEPARATOR, reduced);
}

long get_file_size(FILE* file){
    long fsize;
    struct stat s;
    int fd;

    if ((fd = fileno(file)) < 0){
        fprintf(stderr, "Couldn't open file descriptor for size estimation");
        return -1;
    }
    if ((fstat(fd, &s))){
        fprintf(stderr, "Couldn't get file info for size estimation");
        return -2;
    }
    fsize = s.st_size;

    return fsize;
}

int count_lines(FILE* file) {
    char* buf = malloc(sizeof(char) * IO_BUFF_SIZE);
    int counter = 1;

    for(;;) {
        size_t res = fread(buf, sizeof(char), IO_BUFF_SIZE, file);
        if (ferror(file)){
            fprintf(stderr, "Error encountered when counting lines");
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
