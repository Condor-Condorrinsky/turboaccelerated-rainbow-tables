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
    EXPECT_TRUE(strcmp(getChainPasswd(chains[0]), "password") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[1]), "0xFFE594140401B03240C5660038A6F109") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[2]), "iloveyou") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[3]), "0xD4F5BA191EF3CF22F64D4FA492D07346") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[4]), "sunshine") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[5]), "0x0D971616ECE66D0247B7738F31D5AFA1") == 0);
    EXPECT_TRUE(strcmp(getChainPasswd(chains[6]), "letmein") == 0);
    EXPECT_TRUE(strcmp(getChainHash(chains[7]), "0xDA9A4E2F57E49EAC7D921C9ED08DD280") == 0);

    for (int i = 0; i < entries; i++) {
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
