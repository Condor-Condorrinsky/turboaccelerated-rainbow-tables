#include <gtest/gtest.h>
extern "C" {
#include "../src/tablegen.h"
}

// Whole class with SetUp and TearDown is not really needed here, but I left it
// to keep testing function code cleaner and more readable by leaving out file opening,
// closing etc.
class TableGenFixture : public ::testing::Test{

    protected:
        FILE* in = nullptr;
        FILE* out = nullptr;
        const char* inpath = "../tst/rsrc/commonpasses.txt";
        const char* outpath = "../tst/out/generate_rainbow_table_test.txt";

        void SetUp() override {
            in = fopen(inpath, "r");
            if (in == nullptr) {
                FAIL() << "Couldn't open test file";
            }
            out = fopen(outpath, "wb+");
            if (out == nullptr){
                FAIL() << "Couldn't open output file";
            }
        }

        void TearDown() override {
            if(fclose(in)){
                exit(EXIT_FAILURE);
            }
            if(fclose(out)){
                exit(EXIT_FAILURE);
            }
        };
};

TEST_F(TableGenFixture, GenerateRainbowTableTest){
    generate_rainbow_table(in, out);

    fseek(out, 0, SEEK_SET);
    EXPECT_EQ(count_lines(out), 9);
}

TEST_F(TableGenFixture, GenerateChainTest){
    const char* passwd = "football";
    // Beginning pass - football, chain end hash - value of football
    const char* football = "0xC6285C18FCF1C6322242CAD79460425E";
    unsigned char result[MD5_DIGEST_LENGTH];
    char result_string[HASH_STRING_MIN_LEN];

    generate_chain(passwd, result, sizeof result, REDUCTION_PATTERNS_SIZE);
    convert_md5_to_string(result, result_string, sizeof result_string);
    EXPECT_TRUE(strcmp(result_string, football) == 0);
}
