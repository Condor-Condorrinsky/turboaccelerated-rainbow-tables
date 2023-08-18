#include <gtest/gtest.h>
extern "C" {
    #include "../src/md5calc.h"
}

TEST(MD5CalcTest, ComputeMD5Test){
    // "Hello"
    const char* s = "8b1a9953c4611296a827abf8c47804d7";
    const int hello_length = 5;
    unsigned char digest[MD5_DIGEST_LENGTH];
    char string_digest[2 * MD5_DIGEST_LENGTH + 1];

    unsigned int hash = compute_md5("Hello", digest, hello_length, sizeof digest);
    EXPECT_EQ(hash, MD5_DIGEST_LENGTH) << "Digest length nr 1 not equal" << std::endl;

    convert_to_string(digest, string_digest, sizeof string_digest);
    int result = strcmp(string_digest, s);
    EXPECT_TRUE(result == 0) << "String digest nr 1 not equal" << std::endl;
}

TEST(MD5CalcTest, ConvertToStringTest){
    // 0xea7fc82b5937beff14a7cb274b96b76e
    const unsigned char test_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char out[2 * MD5_DIGEST_LENGTH + 1];

    convert_to_string(test_digest, out, sizeof out);
    int result = strcmp(out, "ea7fc82b5937beff14a7cb274b96b76e");
    EXPECT_TRUE(result == 0);
}
