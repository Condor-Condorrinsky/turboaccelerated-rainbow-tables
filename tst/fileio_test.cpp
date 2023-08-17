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

TEST_F(FileIOFixture, LoadPassDictionaryTest){
    long fsize = get_file_size(f);
    // variable-length array
    char buffer[fsize];
    int num_read;

    num_read = load_pass_dictionary(f, buffer, sizeof buffer);
    EXPECT_EQ(num_read, fsize);
    // Some random character checks
    EXPECT_EQ(buffer[8], '\n');
    EXPECT_EQ(buffer[17], 'l');
    EXPECT_EQ(buffer[28], 'g');
    EXPECT_EQ(buffer[43], 'i');
    EXPECT_EQ(buffer[53], 'm');
}

TEST_F(FileIOFixture, WriteFileTest){
    const char* outpath = "../tst/out/write_file_test.txt";
    const char* expected = "message -> qazwsxed";
    char* out_buffer;

    FILE* out = fopen(outpath, "w+");
    if (out == nullptr){
        FAIL() << "Couldn't write to test file";
    }

    write_line(out, "message", "qazwsxed");

    fread(out_buffer, sizeof(char), strlen(expected), out);
    fclose(out);

    EXPECT_TRUE(strcmp(out_buffer, expected));
}

TEST_F(FileIOFixture, GetFileSizeTest){
    long chars = get_file_size(f);
    EXPECT_EQ(chars, 64);
}

TEST_F(FileIOFixture, CountLinesTest){
    int lines = count_lines(f);
    EXPECT_EQ(lines, 8);
}
