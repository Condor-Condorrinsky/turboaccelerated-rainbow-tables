#include <gtest/gtest.h>
extern "C" {
    #include "../src/md5calc.h"
}

TEST(MD5CalcTest, ComputeMD5Test){
    // "Hello"
    const char* s1 = "8b1a9953c4611296a827abf8c47804d7";
    // "C++ is C with classes"
    const char* s2 = "19cc03bd12cf0e09302c973631ca4e4b";
    // "Change my mind"
    const char* s3 = "b9e284600dfefbc2e078279c42c97f81";

    unsigned char digest1[MD5_DIGEST_LENGTH];
    unsigned char digest2[MD5_DIGEST_LENGTH];
    unsigned char digest3[MD5_DIGEST_LENGTH];

    char string_digest1[2 * MD5_DIGEST_LENGTH + 1];
    char string_digest2[2 * MD5_DIGEST_LENGTH + 1];
    char string_digest3[2 * MD5_DIGEST_LENGTH + 1];

    unsigned int result1 = compute_md5("Hello", digest1);
    unsigned int result2 = compute_md5("C++ is C with classes", digest2);
    unsigned int result3 = compute_md5("Change my mind", digest3);

    EXPECT_EQ(result1, MD5_DIGEST_LENGTH) << "Digest length nr 1 not equal" << std::endl;
    EXPECT_EQ(result2, MD5_DIGEST_LENGTH) << "Digest length nr 2 not equal" << std::endl;
    EXPECT_EQ(result3, MD5_DIGEST_LENGTH) << "Digest length nr 3 not equal" << std::endl;

    convert_to_string(digest1, string_digest1);
    convert_to_string(digest2, string_digest2);
    convert_to_string(digest3, string_digest3);

    EXPECT_TRUE(strcmp(string_digest1, s1)) << "String digest nr 1 not equal" << std::endl;
    EXPECT_TRUE(strcmp(string_digest2, s2)) << "String digest nr 2 not equal" << std::endl;
    EXPECT_TRUE(strcmp(string_digest3, s3)) << "String digest nr 3 not equal" << std::endl;
}

TEST(MD5CalcTest, ConvertToStringTest){
    // 0xea7fc82b5937beff14a7cb274b96b76e
    const unsigned char test_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char out[2 * MD5_DIGEST_LENGTH + 1];
    convert_to_string(test_digest, out);

    EXPECT_TRUE(strcmp(out, "ea7fc82b5937beff14a7cb274b96b76e"));
}
