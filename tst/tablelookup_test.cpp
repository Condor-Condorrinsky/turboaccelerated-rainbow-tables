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

//TEST_F(TableLookUpFixture, ExtractHashedValsTest){
//    char* expected = (char*)
//            "0x83335D91BD32DF9EC3EB862764339A30\n"
//            "0x91908F9B721CCFE45F80F9F8E52DEC6D\n"
//            "0xFE25C6864F5F51E5812A7B1DFBB3C714\n"
//            "0xC7BBECE84749D315B23E321767E73650\n"
//            "0xDF91830460596056D67F1D0AB33C0826\n"
//            "0x6B43A3A51B7B80B6EA146601804FA018\n"
//            "0xF710B0F25A61290806C2C83CDBFCE2B6\n"
//            "0x95984C556491D71D95CEB3934C9A23F1\n";
//    char* table = (char*) malloc(1024 * sizeof(char));
//    char* extracted = (char*) malloc(512 * sizeof(char));
//
//    load_file(in, table, 1024 * sizeof(char));
//    extract_hashed_vals(table, extracted);
//
//    EXPECT_TRUE(strcmp(extracted, expected) == 0);
//
//    free(table);
//    free(extracted);
//}
