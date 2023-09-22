#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/tablegen.h"

typedef struct TABLEGEN_TEST_STRUCT{
    FILE* in;
    FILE* out;
} TABLEGEN_TEST_STRUCT;

static TABLEGEN_TEST_STRUCT tablegenTestStruct = {.in = NULL, .out = NULL};

static int tablegen_setup(void** state){
    const char* inpath = "tst/rsrc/commonpasses.txt";
    const char* outpath = "tst/out/generate_rainbow_table_test.txt";

    tablegenTestStruct.in = fopen(inpath, "r+b");
    if (tablegenTestStruct.in == NULL) {
        fprintf(stderr, "Cannot open input file for tablegen_test.c\n");
        return EXIT_FAILURE;
    }

    tablegenTestStruct.out = fopen(outpath, "r+b");
    if (tablegenTestStruct.out == NULL) {
        fprintf(stderr, "Cannot open input file for tablegen_test.c\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int tablegen_teardown(void** state){
    if(fclose(tablegenTestStruct.in)){
        fprintf(stderr, "Cannot close input file for tablegen_test.c\n");
        return EXIT_FAILURE;
    }
    if(fclose(tablegenTestStruct.out)){
        fprintf(stderr, "Cannot close input file for tablegen_test.c\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void generate_rainbow_table_test(void** state){
    generate_rainbow_table(tablegenTestStruct.in, tablegenTestStruct.out);

    fseek(tablegenTestStruct.out, 0, SEEK_SET);
    assert_int_equal((int) count_lines(tablegenTestStruct.out), 8);
}

static void generate_chain_test(void** state){
    const char* passwd = "piesek";
    const char* expected_hash = "0x7B39E66B371B6E14CBEC97BF22633A6E";
    char result[MAX_REDUCED_PASS_LENGTH];
    char result_string[HASH_STRING_MIN_LEN];

    //generate_chain_verbose(passwd, result, sizeof result, REDUCTION_PATTERNS_SIZE);
    //convert_md5_to_string(result, result_string, sizeof result_string);
    //assert_true(strcmp(result_string, expected_hash) == 0);

    //const char* passwd2 = "10000000";
    //generate_chain_verbose(passwd2, result, sizeof result, REDUCTION_PATTERNS_SIZE);

    //const char* passwd3 = "84260879";
    const char* passwd3 = "35710714";
    generate_chain_verbose(passwd3, result, sizeof result, REDUCTION_PATTERNS_SIZE);
}
