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

TEST_F(TableLookUpFixture, LookupTest){

}

TEST_F(TableLookUpFixture, ExtractHashedValsTest){
    char* expected =
            (char*) "#]>6n=G3\n?hb}x',R\nYGvm{DeP\nJwZ^BJAf\n&Tfs5ky8\nN{jdaMSH\n.{qP1-JA\n7IY?:K7_\n";
    char* table = (char*) malloc(1024 * sizeof(char));
    char* extracted = (char*) malloc(512 * sizeof(char));

    load_file(in, table, 1024 * sizeof(char));
    extract_hashed_vals(table, extracted);

    EXPECT_TRUE(strcmp(extracted, expected) == 0);

    free(table);
    free(extracted);
}

TEST_F(TableLookUpFixture, PerformChainLookupTest){

}
