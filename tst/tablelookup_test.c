#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/tablelookup.h"

typedef struct TABLELOOKUP_TEST_STRUCT{
    FILE* in;
} TABLELOOKUP_TEST_STRUCT;

static TABLELOOKUP_TEST_STRUCT tablelookupTestStruct = {.in=NULL};

static int tablelookup_setup(void** state){
    const char* path = "tst/rsrc/example_rainbow_table.txt";

    FILE* f = fopen(path, "r");
    if (f == NULL) {
        fprintf(stderr, "Cannot open input file for tablelookup_test.c\n");
        return EXIT_FAILURE;
    }
    tablelookupTestStruct.in = f;

    return EXIT_SUCCESS;
}

static int tablelookup_teardown(void** state){
    if(fclose(tablelookupTestStruct.in)){
        fprintf(stderr, "Cannot close input file for tablelookup_test.c\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void lookup_test(void** state){
    const char* hash_to_find = "0xBE874F841F54C94EE7D128C429DA112F";

    int ret = lookup(tablelookupTestStruct.in, hash_to_find);

    assert_int_equal(ret, HASH_FOUND);
}

static void parse_table_meta_test(void** state){
    char* data = "Chain length:16\n"
                 "Charset:ALPHANUMERIC\n"
                 "J4lyVcBN3M|xVaW5KGMvv";
    char data_copy[100];
    char* table_after_parse = malloc(1024 * sizeof(char));
    TableMetadata test;

    strcpy(data_copy, data);
    test = parse_table_meta(data_copy, &table_after_parse);

    assert_int_equal(test.chain_len, 16);
    assert_int_equal(test.charset, ALPHANUMERIC);

    assert_string_equal(table_after_parse, "J4lyVcBN3M|xVaW5KGMvv");

    free(table_after_parse);
}

static void extract_hashed_vals_test(void** state){
    char* table = malloc(1024 * sizeof(char));
    char* table_after_parse = malloc(1024 * sizeof(char));
    unsigned int entries = count_lines(tablelookupTestStruct.in);
    PassHashChain **chains = malloc(entries * sizeof chains);

    for (int i = 0; i < entries; i++) {
        chains[i] = newChain();
    }

    load_file(tablelookupTestStruct.in, table, 1024 * sizeof(char));
    parse_table_meta(table, &table_after_parse);
    extract_hashed_vals(table_after_parse, chains);

    // Some random checks
    assert_string_equal(getChainPasswd(chains[0]), "12345678");
    assert_string_equal(getChainEnd(chains[1]), "57891609");
    assert_string_equal(getChainPasswd(chains[2]), "24680246");
    assert_string_equal(getChainEnd(chains[3]), "26528654");
    assert_string_equal(getChainPasswd(chains[4]), "13579135");
    assert_string_equal(getChainEnd(chains[5]), "61678808");
    assert_string_equal(getChainPasswd(chains[6]), "00000001");
    assert_string_equal(getChainEnd(chains[7]), "35719766");

    for (int i = 0; i < entries; i++) {
        deleteChain(chains[i]);
    }

    free(table);
    free(table_after_parse);
    free(chains);
}

static void line_to_PassHashChain_test(void** state){
    const char* line = "10000000|35719766";
    char line_copy[100];

    safer_strncpy(line_copy, line, 100);
    PassHashChain* c = newChain();
    line_to_PassHashChain(line_copy, c);

    assert_string_equal(getChainPasswd(c), "10000000");
    assert_string_equal(getChainEnd(c), "35719766");

    deleteChain(c);
}

static void find_hash_test(void** state){
    const char* looked = "0xBE874F841F54C94EE7D128C429DA112F";
    char* table = malloc(1024 * sizeof(char));
    char* table_after_meta = malloc(1024 * sizeof(char));
    unsigned int entries = count_lines(tablelookupTestStruct.in) - 2;
    PassHashChain **chains = malloc(entries * sizeof chains);
    TableMetadata meta;

    for (int i = 0; i < entries; i++) {
        chains[i] = newChain();
    }

    load_file(tablelookupTestStruct.in, table, 1024 * sizeof(char));
    meta = parse_table_meta(table, &table_after_meta);
    extract_hashed_vals(table_after_meta, chains);

    int ret = find_hash(chains, entries, looked, "100000000", &meta);

    assert_int_equal(ret, HASH_FOUND);

    for (int i = 0; i < entries; i++) {
        deleteChain(chains[i]);
    }

    free(table);
    free(table_after_meta);
    free(chains);
}

static void find_hash_in_chain_test(void** state){
    char* passwd = "97531975";
    char* chain_hash = "61678808";
    char* hash_to_look = "0xBE874F841F54C94EE7D128C429DA112F";
    char* hash_to_look_not_present = "0x1234567890ABCDEF1234567890ABCDEF";
    TableMetadata meta = {.chain_len=32, .charset=DIGITS};
    PassHashChain* c = newChain();
    setChainPasswd(c, passwd);
    setChainEnd(c, chain_hash);

    int result = find_hash_in_chain(c, hash_to_look, "100000000", &meta);
    int result2 = find_hash_in_chain(c, hash_to_look_not_present, "100000000", &meta);

    assert_int_equal(result, HASH_FOUND);
    assert_int_equal(result2, HASH_NOT_FOUND);

    deleteChain(c);
}

static void str_to_uppercase_test(void** state){
    const char* input = "p@s5wd";
    char output[7];

    str_to_uppercase(input, output, sizeof output);

    assert_string_equal(output, "P@S5WD");
}
