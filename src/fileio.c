#include "fileio.h"

int load_pass_dictionary(FILE* file, char* buffer, unsigned int buffer_len){
    int bytes_read = 0;

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

    return bytes_read;
}

void write_line(FILE* file, const char* pass, const char* reduced){
    fprintf(file, "%s%c%s\n", pass, RAINBOW_TABLE_SEPARATOR, reduced);
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
    char buf[IO_BUFF_SIZE];
    int counter = 1;

    for(;;) {
        size_t res = fread(buf, sizeof(char), IO_BUFF_SIZE, file);
        if (ferror(file)){
            fprintf(stderr, "Error encountered when counting lines");
            return IO_EXIT_FAILURE;
        }

        for (int i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (res == 0)
            break;
    }

    return counter;
}

struct tm get_curr_datetime(){
    time_t t = time(NULL);
    struct tm curr_time = *localtime(&t);
    // printf("now: %d-%02d-%02d %02d:%02d:%02d\n",
    //      tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return curr_time;
}
