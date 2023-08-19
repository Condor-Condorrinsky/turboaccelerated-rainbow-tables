#include <gtest/gtest.h>
extern "C" {
    #include "../src/reduction.h"
}

TEST(ReductionTest, ReduceTest){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_buffer[MD5_DIGEST_LENGTH + 1];
    const char* pattern = "15_10_7_12_3_0_8_1";

    reduce(example_digest, output_buffer, pattern, sizeof output_buffer);

    int result = strcmp(output_buffer, "gvvxraux");
    printf("%s\n", output_buffer);
    EXPECT_TRUE(result == 0) << "Reduction output not equal to expected value";
}

TEST(ReductionTest, SafeStrncpyTest){
    const char* test = "abcdefghijklmnopqrstuwvxyz0123456789";
    unsigned int test_len = 26 + 10 + 1;
    char good_copy[test_len];
    char bad_copy[test_len - 5];

    safe_strncpy(good_copy, test, sizeof good_copy);
    EXPECT_TRUE(strcmp(good_copy, test) == 0);

    safe_strncpy(bad_copy, test, sizeof bad_copy);
    EXPECT_EQ(bad_copy[test_len - 5 - 1], '\0');
}

TEST(ReductionTest, SplitByUnderscoresTest){
    const char* pattern = "15_10_7_12_3_0_8_1";
    char pattern_copy[48];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];

    safe_strncpy(pattern_copy, pattern, sizeof pattern_copy);
    split_by_underscores(pattern_copy, pattern_tokenized, sizeof pattern_tokenized);

    EXPECT_EQ(pattern_tokenized[0], 15);
    EXPECT_EQ(pattern_tokenized[1], 10);
    EXPECT_EQ(pattern_tokenized[2], 7);
    EXPECT_EQ(pattern_tokenized[3], 12);
    EXPECT_EQ(pattern_tokenized[4], 3);
    EXPECT_EQ(pattern_tokenized[5], 0);
    EXPECT_EQ(pattern_tokenized[6], 8);
    EXPECT_EQ(pattern_tokenized[7], 1);
}
