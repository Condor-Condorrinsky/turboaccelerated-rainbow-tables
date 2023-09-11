#include <gtest/gtest.h>
extern "C" {
    #include "../src/fileio.h"
}

class FileIOFixture : public ::testing::Test{

    protected:
        FILE* f = nullptr;
        const char* path = "../tst/rsrc/commonpasses.txt";

        void SetUp() override {
            f = fopen(path, "r");
            if (f == nullptr) {
                FAIL() << "Couldn't open test file";
            }
        }

        void TearDown() override {
            if(fclose(f)){
                exit(EXIT_FAILURE);
            }
        };
};

TEST_F(FileIOFixture, LoadFileTest){
    long fsize = get_file_size(f);
    // variable-length array
    char buffer[fsize + 1];
    int num_read;

    num_read = load_file(f, buffer, sizeof buffer);
    EXPECT_EQ(num_read, fsize);
    // Some random character checks
    EXPECT_EQ(buffer[6], '\n');
    EXPECT_EQ(buffer[12], 'y');
    EXPECT_EQ(buffer[21], 'd');
    EXPECT_EQ(buffer[37], 'i');
    EXPECT_EQ(buffer[53], 'e');
}

TEST_F(FileIOFixture, GetFileSizeTest){
    long chars = get_file_size(f);
    EXPECT_EQ(chars, 56);
}

TEST_F(FileIOFixture, CountLinesTest){
    unsigned int lines = count_lines(f);
    EXPECT_EQ(lines, 8);
}
