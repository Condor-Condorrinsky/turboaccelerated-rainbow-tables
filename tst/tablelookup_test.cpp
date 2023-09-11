#include <gtest/gtest.h>
extern "C" {
    #include "../src/tablelookup.h"
}

class TableLookUpFixture : public ::testing::Test{

protected:
    FILE* in = nullptr;
    const char* inpath = "../tst/rsrc/example_rainbow_table.txt";

    void SetUp() override {
        in = fopen(inpath, "r+b");
        if (in == nullptr) {
            FAIL() << "Couldn't open test file";
        }
    }

    void TearDown() override {
        if(fclose(in)){
            exit(EXIT_FAILURE);
        }
    };
};

/*
 * Just a function to check whether the program crashes or not.
 * It's hard to write tests for full table look up because, well,
 * I'd have to reverse one of the hashes in the example file myself...
 */
TEST_F(TableLookUpFixture, LookupTest){
    const char* hash_to_find = (char*) "0xA1B9A93535A93CC9496DA9E47F52CBE8";
    int ret;

    ret = lookup(in, hash_to_find);
}

TEST_F(TableLookUpFixture, ExtractHashedValsTest){
    char* table = (char*) malloc(1024 * sizeof(char));
    unsigned int entries = count_lines(in);
    // static_cast<...> is required by C++, in C a simple malloc call suffices
    PassHashChain **chains = static_cast<PassHashChain **>(malloc(entries * sizeof chains));

    for (int i = 0; i < entries; i++) {
        chains[i] = newChain();
    }

    load_file(in, table, 1024 * sizeof(char));
    extract_hashed_vals(table, chains);

    // Some random checks
    EXPECT_TRUE(strcmp(getChainPasswd(chains[0]), "passwd") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[1]), "0x6552A9BAD80DC542814207DAAB2053F8") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[2]), "ilovey") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[3]), "0x4EB1347DCDBE1138B223D86A14C34A93") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[4]), "sunsun") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[5]), "0x7035F9D5AA9ACF8F4C277B73DC17F88C") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[6]), "trains") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[7]), "0xA8EF4084FE17272B7DAB9492CFCB6703") == 0);

    for (int i = 0; i < entries; i++) {
        deleteChain(chains[i]);
    }

    free(table);
    free(chains);
}

TEST_F(TableLookUpFixture, LineToPassHashChainTest){
    const char* line = "passwd|0xE6AB903BDD7A391A7E3E3B1588033676";
    char line_copy[100];

    safer_strncpy(line_copy, line, 100);
    PassHashChain* c = newChain();
    line_to_PassHashChain(line_copy, c);

    EXPECT_TRUE(strcmp(getChainPasswd(c), "passwd") == 0);
    EXPECT_TRUE(strcmp(getChainHash(c), "0xE6AB903BDD7A391A7E3E3B1588033676") == 0);

    deleteChain(c);
}

TEST_F(TableLookUpFixture, FindHashTest){
    const char* looked = (char*) "0x37B4E2D82900D5E94B8DA524FBEB33C0";
    char* table = (char*) malloc(1024 * sizeof(char));
    unsigned int entries = count_lines(in);
    // static_cast<...> is required by C++, in C a simple malloc call suffices
    PassHashChain **chains = static_cast<PassHashChain **>(malloc(entries * sizeof chains));

    for (int i = 0; i < entries; i++) {
        chains[i] = newChain();
    }

    load_file(in, table, 1024 * sizeof(char));
    extract_hashed_vals(table, chains);

    find_hash(chains, entries, looked);

    for (int i = 0; i < entries; i++) {
        deleteChain(chains[i]);
    }

    free(table);
    free(chains);
}

// TODO: Still appears to not find hash in chain when it should
TEST_F(TableLookUpFixture, FindHashInChainTest){
    char* passwd = (char*) "football";
    char* chain_hash = (char*) "0x8C90875D218107A4C1AE1C4EB3B926CF";
    char* hash_to_look = (char*) "0x37B4E2D82900D5E94B8DA524FBEB33C0";
    PassHashChain* c = newChain();
    setChainPasswd(c, passwd);
    setChainHash(c, chain_hash);

    int result = find_hash_in_chain(c, hash_to_look);

    EXPECT_EQ(result, HASH_FOUND);

    deleteChain(c);
}

TEST_F(TableLookUpFixture, StrToUppercaseTest){
    const char* input = "p@s5wd";
    char output[7];

    str_to_uppercase(input, output, sizeof output);

    EXPECT_TRUE(strcmp(output, "P@S5WD") == 0);
}
