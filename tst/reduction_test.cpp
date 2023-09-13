#include <gtest/gtest.h>
extern "C" {
    #include <gmp.h>
    #include "../src/reduction.h"
    #include "../src/patternenum.h"
}

TEST(ReductionTest, RTest){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_buffer[MAX_REDUCED_PASS_LENGTH];

    R(example_digest, output_buffer, sizeof output_buffer, (char*) "2");
}

TEST(ReductionTest, ReduceTest){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_buffer[MAX_REDUCED_PASS_LENGTH];
    const char* pattern = "15_10_7_12_3_0_8_1";

    reduce(example_digest, output_buffer, pattern, sizeof output_buffer, GEN_TABLE_PASS_LEN);

    int result = strcmp(output_buffer, "gvvxra");
    EXPECT_TRUE(result == 0) << "Reduction output not equal to expected value";
}

TEST(ReductionTest, SaferStrncpyTest){
    const char* test = "abcdefghijklmnopqrstuwvxyz0123456789";
    unsigned int test_len = 26 + 10 + 1;
    char good_copy[test_len];
    // char bad_copy[test_len - 5];

    safer_strncpy(good_copy, test, sizeof good_copy);
    EXPECT_TRUE(strcmp(good_copy, test) == 0);

    // safe_strncpy(bad_copy, test, sizeof bad_copy);
    // EXPECT_EQ(bad_copy[test_len - 5 - 1], '\0');
}

TEST(ReductionTest, SplitByUnderscoresTest){
    const char* pattern = "15_10_7_12_3_0_8_1";
    char pattern_copy[48];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];

    safer_strncpy(pattern_copy, pattern, sizeof pattern_copy);
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

TEST(ReductionTest, UnsignedCharToAsciiTest){
    unsigned char backspace = 8;
    unsigned char space = 32;
    unsigned char four = 52;
    unsigned char capital_k = 75;
    unsigned char left_square_bracket = 91;
    unsigned char del = 127;
    unsigned char random_val = 213;

    char backspace_converted = unsigned_char_to_ascii(backspace);
    char space_converted = unsigned_char_to_ascii(space);
    char four_converted = unsigned_char_to_ascii(four);
    char capital_k_converted = unsigned_char_to_ascii(capital_k);
    char left_square_bracket_converted = unsigned_char_to_ascii(left_square_bracket);
    char del_converted = unsigned_char_to_ascii(del);
    char random_val_converted = unsigned_char_to_ascii(random_val);

    EXPECT_EQ(backspace_converted, 41);
    EXPECT_EQ(space_converted, 65);
    EXPECT_EQ(four_converted, 85);
    EXPECT_EQ(capital_k_converted, 108);
    EXPECT_EQ(left_square_bracket_converted, 33);
    EXPECT_EQ(del_converted, 67);
    EXPECT_EQ(random_val_converted, 60);
}

TEST(ReductionTest, UnsignedCharToSmallLetterTest){
    unsigned char backspace = 8;
    unsigned char space = 32;
    unsigned char four = 52;
    unsigned char capital_k = 75;
    unsigned char left_square_bracket = 91;
    unsigned char del = 127;
    unsigned char random_val = 213;

    char backspace_converted = unsigned_char_to_small_letter(backspace);
    char space_converted = unsigned_char_to_small_letter(space);
    char four_converted = unsigned_char_to_small_letter(four);
    char capital_k_converted = unsigned_char_to_small_letter(capital_k);
    char left_square_bracket_converted = unsigned_char_to_small_letter(left_square_bracket);
    char del_converted = unsigned_char_to_small_letter(del);
    char random_val_converted = unsigned_char_to_small_letter(random_val);

    EXPECT_EQ(backspace_converted, 105);
    EXPECT_EQ(space_converted, 103);
    EXPECT_EQ(four_converted, 97);
    EXPECT_EQ(capital_k_converted, 120);
    EXPECT_EQ(left_square_bracket_converted, 110);
    EXPECT_EQ(del_converted, 120);
    EXPECT_EQ(random_val_converted, 102);
}
