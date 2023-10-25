#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/tablegen.h"

typedef struct TABLEGEN_TEST_STRUCT{
    FILE* in;
    FILE* out;
    TableMetadata meta;
} TABLEGEN_TEST_STRUCT;

static TABLEGEN_TEST_STRUCT tablegenTestStruct =
        {.in = NULL, .out = NULL, .meta = {.chain_len = 0, .charset = DIGITS}};

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

    tablegenTestStruct.meta.chain_len = 32;
    tablegenTestStruct.meta.charset = DIGITS;

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
    generate_rainbow_table(tablegenTestStruct.in, tablegenTestStruct.out, &tablegenTestStruct.meta);

    rewind(tablegenTestStruct.out);
    assert_int_equal((int) count_lines(tablegenTestStruct.out), 8);
}

static void generate_chain_test(void** state){
    const char* passwd = "97531975";
    const char* expected_result = "61678808";
    char result[MAX_REDUCED_PASS_LENGTH];
    char set_size[SET_SIZE_BUFFER];

    calc_set_size(strlen(passwd), DIGITS, set_size, sizeof set_size);
    generate_chain(passwd, result, sizeof result, tablegenTestStruct.meta.chain_len, set_size, tablegenTestStruct.meta.charset);

    assert_string_equal(result, expected_result);
}

static void iter_itoa_test(void** state){
    char ten[20];
    char big[20];
    char neg[20];
    char zero[20];

    iter_itoa(10, ten, sizeof ten);
    iter_itoa(14124155, big, sizeof big);
    iter_itoa(-23535, neg, sizeof neg);
    iter_itoa(0, zero, sizeof zero);

    assert_string_equal(ten, "10");
    assert_string_equal(big, "14124155");
    assert_string_equal(neg, "-23535");
    assert_string_equal(zero, "0");
}
