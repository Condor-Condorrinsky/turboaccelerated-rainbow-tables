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

    lookup(in, hash_to_find);
}

TEST_F(TableLookUpFixture, ExtractHashedValsTest){
    char* table = (char*) malloc(1024 * sizeof(char));
    int entries = count_lines(in);
    // static_cast<...> is required by C++, in C a simple malloc call suffices
    PassHashChain **chains = static_cast<PassHashChain **>(malloc(entries * sizeof chains));

    for (int i = 0; i < entries - 1; i++) {
        chains[i] = newChain();
    }

    load_file(in, table, 1024 * sizeof(char));
    extract_hashed_vals(table, chains);

    // Some random checks
    EXPECT_TRUE(strcmp(getChainPasswd(chains[0]), "password") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[1]), "0x91908F9B721CCFE45F80F9F8E52DEC6D") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[2]), "iloveyou") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[3]), "0xC7BBECE84749D315B23E321767E73650") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[4]), "sunshine") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[5]), "0x6B43A3A51B7B80B6EA146601804FA018") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[6]), "letmein") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[7]), "0x95984C556491D71D95CEB3934C9A23F1") == 0);

    for (int i = 0; i < entries - 1; ++i) {
        deleteChain(chains[i]);
    }

    free(table);
    free(chains);
}

TEST_F(TableLookUpFixture, LineToPassHashChainTest){
    const char* line = "football|0xC6285C18FCF1C6322242CAD79460425E";
    char line_copy[100];

    safer_strncpy(line_copy, line, 100);
    PassHashChain* c = newChain();
    line_to_PassHashChain(line_copy, c);

    EXPECT_TRUE(strcmp(getChainPasswd(c), "football") == 0);
    EXPECT_TRUE(strcmp(getChainHash(c), "0xC6285C18FCF1C6322242CAD79460425E") == 0);
}