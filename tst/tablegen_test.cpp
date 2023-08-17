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
            out = fopen(outpath, "w+");
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

// TODO: finish this test
TEST_F(TableGenFixture, GenerateRainbowTableTest){
    generate_rainbow_table(in, out);

    // EXPECT_EQ(count_lines(out), 9);
}
