#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/fileio.h"

typedef struct FILEIO_TEST_STRUCT{
    FILE* in;
} FILEIO_TEST_STRUCT;

static FILEIO_TEST_STRUCT fileioTestStruct = {.in = NULL};

static int fileio_setup(void** state){
    const char* path = "tst/rsrc/commonpasses.txt";

    FILE* f = fopen(path, "r");
    if (f == NULL) {
        fprintf(stderr, "Cannot open input file for fileio_test.c\n");
        return EXIT_FAILURE;
    }
    fileioTestStruct.in = f;

    return EXIT_SUCCESS;
}

static int fileio_teardown(void** state){
    if(fclose(fileioTestStruct.in)){
        fprintf(stderr, "Cannot close input file for fileio_test.c\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void load_file_test(void** state){
    long fsize = get_file_size(fileioTestStruct.in);
    // variable-length array
    char buffer[fsize + 1];
    int num_read;

    num_read = load_file(fileioTestStruct.in, buffer, sizeof buffer);
    assert_int_equal(num_read, fsize);
    // Some random character checks
    assert_int_equal((int) buffer[8], (int) '\n');
    assert_int_equal((int) buffer[13], (int) '4');
    assert_int_equal((int) buffer[23], (int) '2');
    assert_int_equal((int) buffer[38], (int) '5');
    assert_int_equal((int) buffer[54], (int) '0');
}

static void get_file_size_test(void** state){
    long chars = get_file_size(fileioTestStruct.in);
    assert_int_equal((int) chars, 72);
}

static void count_lines_test(void** state){
    unsigned int lines = count_lines(fileioTestStruct.in);
    assert_int_equal((int) lines, 8);
}
