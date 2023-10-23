#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/reduction.h"

static void R_test(void** state){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_digits[MAX_REDUCED_PASS_LENGTH];
    char output_alphanumeric[MAX_REDUCED_PASS_LENGTH];
    char output_ascii[MAX_REDUCED_PASS_LENGTH];
    // 10^8
    char* set_size_digits = "100000000";
    // 62^8
    char* set_size_alphanumeric = "218340105584896";
    // 93^8
    char* set_size_ascii = "5595818096650401";

    R(example_digest, output_digits, sizeof output_digits,
      "2", set_size_digits, 8, DIGITS);
    R(example_digest, output_alphanumeric, sizeof output_alphanumeric,
      "2", set_size_alphanumeric, 8, ALPHANUMERIC);
    R(example_digest, output_ascii, sizeof output_ascii,
      "2", set_size_ascii, 8, ASCII_PRINTABLE);

    assert_string_equal(output_digits, "00838512");
    assert_string_equal(output_alphanumeric, "B9WV6QMO");
    assert_string_equal(output_ascii, "XSjHj_R7");
}

static void encode_result_test(void** state){
    char* number = "40527010";
    char output1[16];
    char output2[16];
    char output3[16];

    encode_result(DIGITS, 7, number, output1, sizeof output1);
    assert_string_equal(output1, "4052701");
    encode_result(ALPHANUMERIC, 7, number, output2, sizeof output2);
    assert_string_equal(output2, "eq8AA8q");
    encode_result(ASCII_PRINTABLE, 7, number, output3, sizeof output3);
    assert_string_equal(output3, "IUg++gU");

    encode_result(DIGITS, 12, number, output1, sizeof output1);
    assert_string_equal(output1, "000040527010");
    encode_result(ALPHANUMERIC, 12, number, output2, sizeof output2);
    assert_string_equal(output2, "00eq8AA8qe00");
    encode_result(ASCII_PRINTABLE, 12, number, output3, sizeof output3);
    assert_string_equal(output3, "!!IUg++gUI!!");
}

static void encode_test(void** state){
    char* number = "123456789";
    char output1[16];
    char output2[16];

    encode(number, 7, ALPHANUMERIC, output1, sizeof output1);
    assert_string_equal(output1, "CYuGR5j");

    encode(number, 7, ASCII_PRINTABLE, output2, sizeof output2);
    assert_string_equal(output2, "-CYozdN");
}

static void pad_str_leading_zeroes_test(void** state){
    char* num1 = "12345678";
    char* num2 = "1";
    char* num3 = "0315926";
    char buf1[10];
    char buf2[10];
    char buf3[10];

    pad_str_leading_zeroes(num1, 8, buf1, sizeof buf1);
    pad_str_leading_zeroes(num2, 8, buf2, sizeof buf2);
    pad_str_leading_zeroes(num3, 8, buf3, sizeof buf3);

    assert_string_equal(buf1, "12345678");
    assert_string_equal(buf2, "00000001");
    assert_string_equal(buf3, "00315926");
}

static void safer_strncpy_test(void** state){
    const char* test = "abcdefghijklmnopqrstuwvxyz0123456789";
    unsigned int test_len = 26 + 10 + 1;
    char good_copy[test_len];
    // char bad_copy[test_len - 5];

    safer_strncpy(good_copy, test, sizeof good_copy);
    assert_string_equal(good_copy, test);

    // safer_strncpy(bad_copy, test, sizeof bad_copy);
    // assert_int_equal((int) bad_copy[test_len - 5 - 1], (int) '\0');
}

static void uchar_to_ascii_test(void** state){
    unsigned char backspace = 8;
    unsigned char space = 32;
    unsigned char four = 52;
    unsigned char capital_k = 75;
    unsigned char left_square_bracket = 91;
    unsigned char del = 127;
    unsigned char random_val = 213;

    char backspace_converted = uchar_to_ascii(backspace);
    char space_converted = uchar_to_ascii(space);
    char four_converted = uchar_to_ascii(four);
    char capital_k_converted = uchar_to_ascii(capital_k);
    char left_square_bracket_converted = uchar_to_ascii(left_square_bracket);
    char del_converted = uchar_to_ascii(del);
    char random_val_converted = uchar_to_ascii(random_val);

    assert_int_equal((int) backspace_converted, 41);
    assert_int_equal((int) space_converted, 65);
    assert_int_equal((int) four_converted, 85);
    assert_int_equal((int) capital_k_converted, 108);
    assert_int_equal((int) left_square_bracket_converted, 125);
    assert_int_equal((int) del_converted, 67);
    assert_int_equal((int) random_val_converted, 60);
}

static void uchar_to_alphanumeric_test(void** state){
    unsigned char backspace = 8;
    unsigned char space = 32;
    unsigned char four = 52;
    unsigned char capital_k = 75;
    unsigned char left_square_bracket = 91;
    unsigned char del = 127;
    unsigned char random_val = 213;

    char backspace_converted = uchar_to_alphanumeric(backspace);
    char space_converted = uchar_to_alphanumeric(space);
    char four_converted = uchar_to_alphanumeric(four);
    char capital_k_converted = uchar_to_alphanumeric(capital_k);
    char left_square_bracket_converted = uchar_to_alphanumeric(left_square_bracket);
    char del_converted = uchar_to_alphanumeric(del);
    char random_val_converted = uchar_to_alphanumeric(random_val);

    assert_int_equal((int) backspace_converted, 56);
    assert_int_equal((int) space_converted, 87);
    assert_int_equal((int) four_converted, 113);
    assert_int_equal((int) capital_k_converted, 68);
    assert_int_equal((int) left_square_bracket_converted, 84);
    assert_int_equal((int) del_converted, 51);
    assert_int_equal((int) random_val_converted, 82);
}
