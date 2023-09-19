#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/patternenum.h"
#include "../src/reduction.h"

static void R_test(void** state){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_buffer[MAX_REDUCED_PASS_LENGTH];

    R(example_digest, output_buffer, sizeof output_buffer, (char*) "2");

    assert_string_equal(output_buffer, "wetouj");
}

static void encode_test(void** state){
    char* num = "305674123";
    unsigned int des_len = 8;
    char output[8+1];

    char* num2 = "1";
    unsigned int des_len2 = 10;
    char output2[10+1];

    char* num3 = "45097";
    unsigned int des_len3 = 4;
    char output3[4+1];

    encode(num, des_len, output, sizeof output);
    encode(num2, des_len2, output2, sizeof output2);
    encode(num3, des_len3, output3, sizeof output3);

    assert_string_equal(output, "eewmxppf");
    assert_string_equal(output2, "aaaabaaaaa");
    assert_string_equal(output3, "aatj");
}

static void pad_str_leading_zeroes_test(void** state){
    char* num1 = "123456789";
    char* num2 = "1";
    char* num3 = "03000000";
    char buf1[10];
    char buf2[10];
    char buf3[10];

    pad_str_leading_zeroes(num1, 9, buf1, sizeof buf1);
    pad_str_leading_zeroes(num2, 9, buf2, sizeof buf2);
    pad_str_leading_zeroes(num3, 9, buf3, sizeof buf3);

    assert_string_equal(buf1, "123456789");
    assert_string_equal(buf2, "000000001");
    assert_string_equal(buf3, "003000000");
}

static void reduce_test(void** state){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_buffer[MAX_REDUCED_PASS_LENGTH];
    const char* pattern = "15_10_7_12_3_0_8_1";

    reduce(example_digest, output_buffer, pattern, sizeof output_buffer, GEN_TABLE_PASS_LEN);
    assert_string_equal(output_buffer, "gvvxra");
}

static void safer_strncpy_test(void** state){
    const char* test = "abcdefghijklmnopqrstuwvxyz0123456789";
    unsigned int test_len = 26 + 10 + 1;
    char good_copy[test_len];
    // char bad_copy[test_len - 5];

    safer_strncpy(good_copy, test, sizeof good_copy);
    assert_string_equal(good_copy, test);

    // safe_strncpy(bad_copy, test, sizeof bad_copy);
    // assert_int_equal((int) bad_copy[test_len - 5 - 1], (int) '\0');
}

static void split_by_underscores_test(void** state){
    const char* pattern = "15_10_7_12_3_0_8_1";
    char pattern_copy[48];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];

    safer_strncpy(pattern_copy, pattern, sizeof pattern_copy);
    split_by_underscores(pattern_copy, pattern_tokenized, sizeof pattern_tokenized);

    assert_int_equal((int) pattern_tokenized[0], 15);
    assert_int_equal((int) pattern_tokenized[1], 10);
    assert_int_equal((int) pattern_tokenized[2], 7);
    assert_int_equal((int) pattern_tokenized[3], 12);
    assert_int_equal((int) pattern_tokenized[4], 3);
    assert_int_equal((int) pattern_tokenized[5], 0);
    assert_int_equal((int) pattern_tokenized[6], 8);
    assert_int_equal((int) pattern_tokenized[7], 1);
}

static void unsigned_char_to_ascii_test(void** state){
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

    assert_int_equal((int) backspace_converted, 41);
    assert_int_equal((int) space_converted, 65);
    assert_int_equal((int) four_converted, 85);
    assert_int_equal((int) capital_k_converted, 108);
    assert_int_equal((int) left_square_bracket_converted, 33);
    assert_int_equal((int) del_converted, 67);
    assert_int_equal((int) random_val_converted, 60);
}

static void unsigned_char_to_small_letter_test(void** state){
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

    assert_int_equal((int) backspace_converted, 105);
    assert_int_equal((int) space_converted, 103);
    assert_int_equal((int) four_converted, 97);
    assert_int_equal((int) capital_k_converted, 120);
    assert_int_equal((int) left_square_bracket_converted, 110);
    assert_int_equal((int) del_converted, 120);
    assert_int_equal((int) random_val_converted, 102);
}
