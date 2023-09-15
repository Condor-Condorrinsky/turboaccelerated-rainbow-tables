#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/tablelookup.h"

typedef struct TABLELOOKUP_TEST_STRUCT{
    FILE* in;
} TABLELOOKUP_TEST_STRUCT;

static TABLELOOKUP_TEST_STRUCT tablelookupTestStruct = {.in = NULL};

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
    const char* hash_to_find = (char*) "0xA1B9A93535A93CC9496DA9E47F52CBE8";
    int ret;

    ret = lookup(tablelookupTestStruct.in, hash_to_find);
}

static void extract_hashed_vals_test(void** state){
    char* table = (char*) malloc(1024 * sizeof(char));
    unsigned int entries = count_lines(tablelookupTestStruct.in);
    PassHashChain **chains = malloc(entries * sizeof chains);

    for (int i = 0; i < entries; i++) {
        chains[i] = newChain();
    }

    load_file(tablelookupTestStruct.in, table, 1024 * sizeof(char));
    extract_hashed_vals(table, chains);

    // Some random checks
    assert_true(strcmp(getChainPasswd(chains[0]), "passwd") == 0);
    assert_true(strcmp(getChainHash(chains[1]), "0x6552A9BAD80DC542814207DAAB2053F8") == 0);
    assert_true(strcmp(getChainPasswd(chains[2]), "ilovey") == 0);
    assert_true(strcmp(getChainHash(chains[3]), "0x4EB1347DCDBE1138B223D86A14C34A93") == 0);
    assert_true(strcmp(getChainPasswd(chains[4]), "sunsun") == 0);
    assert_true(strcmp(getChainHash(chains[5]), "0x7035F9D5AA9ACF8F4C277B73DC17F88C") == 0);
    assert_true(strcmp(getChainPasswd(chains[6]), "trains") == 0);
    assert_true(strcmp(getChainHash(chains[7]), "0xA8EF4084FE17272B7DAB9492CFCB6703") == 0);

    for (int i = 0; i < entries; i++) {
        deleteChain(chains[i]);
    }

    free(table);
    free(chains);
}

static void line_to_PassHashChain_test(void** state){
    const char* line = "passwd|0xE6AB903BDD7A391A7E3E3B1588033676";
    char line_copy[100];

    safer_strncpy(line_copy, line, 100);
    PassHashChain* c = newChain();
    line_to_PassHashChain(line_copy, c);

    assert_true(strcmp(getChainPasswd(c), "passwd") == 0);
    assert_true(strcmp(getChainHash(c), "0xE6AB903BDD7A391A7E3E3B1588033676") == 0);

    deleteChain(c);
}

static void find_hash_test(void** state){
    const char* looked = (char*) "0x37B4E2D82900D5E94B8DA524FBEB33C0";
    char* table = (char*) malloc(1024 * sizeof(char));
    unsigned int entries = count_lines(tablelookupTestStruct.in);
    PassHashChain **chains = malloc(entries * sizeof chains);

    for (int i = 0; i < entries; i++) {
        chains[i] = newChain();
    }

    load_file(tablelookupTestStruct.in, table, 1024 * sizeof(char));
    extract_hashed_vals(table, chains);

    find_hash(chains, entries, looked);

    for (int i = 0; i < entries; i++) {
        deleteChain(chains[i]);
    }

    free(table);
    free(chains);
}

// TODO: Still appears to not find hash in chain when it should
static void find_hash_in_chain_test(void** state){
    char* passwd = (char*) "qwerty";
    char* chain_hash = (char*) "0x6552A9BAD80DC542814207DAAB2053F8";
    char* hash_to_look = (char*) "0xD8578EDF8458CE06FBC5BB76A58C5CA4";
    PassHashChain* c = newChain();
    setChainPasswd(c, passwd);
    setChainHash(c, chain_hash);

    int result = find_hash_in_chain(c, hash_to_look);

    assert_int_equal(result, HASH_FOUND);

    deleteChain(c);
}

static void str_to_uppercase_test(void** state){
    const char* input = "p@s5wd";
    char output[7];

    str_to_uppercase(input, output, sizeof output);

    assert_true(strcmp(output, "P@S5WD") == 0);
}
