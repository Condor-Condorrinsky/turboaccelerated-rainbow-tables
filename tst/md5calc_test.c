#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/md5calc.h"

static void compute_md5_test(void** state){
    // "Hello"
    const char* s = "0x8B1A9953C4611296A827ABF8C47804D7";
    unsigned char digest[MD5_DIGEST_LENGTH];
    char string_digest[HASH_STRING_MIN_LEN];

    unsigned int hash = compute_md5("Hello", digest, sizeof digest);
    assert_int_equal((int) hash, MD5_DIGEST_LENGTH);

    convert_md5_to_string(digest, string_digest, sizeof string_digest);
    assert_true(strcmp(string_digest, s) == 0);
}

static void convert_md5_to_string_test(void** state){
    // 0xea7fc82b5937beff14a7cb274b96b76e
    const unsigned char test_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char out[HASH_STRING_MIN_LEN];

    convert_md5_to_string(test_digest, out, sizeof out);
    assert_true(strcmp(out, "0xEA7FC82B5937BEFF14A7CB274B96B76E") == 0);
}

static void convert_string_to_md5_test(void** state){
    const char* string_hash = "0xEA7FC82B5937BEFF14A7CB274B96B76E";
    unsigned char hash[MD5_DIGEST_LENGTH];

    convert_string_to_md5(string_hash, hash, sizeof hash);
    assert_int_equal((int) hash[0], 234);
    assert_int_equal((int) hash[1], 127);
    assert_int_equal((int) hash[2], 200);
    assert_int_equal((int) hash[3], 43);
    assert_int_equal((int) hash[4], 89);
    assert_int_equal((int) hash[5], 55);
    assert_int_equal((int) hash[6], 190);
    assert_int_equal((int) hash[7], 255);
    assert_int_equal((int) hash[8], 20);
    assert_int_equal((int) hash[9], 167);
    assert_int_equal((int) hash[10], 203);
    assert_int_equal((int) hash[11], 39);
    assert_int_equal((int) hash[12], 75);
    assert_int_equal((int) hash[13], 150);
    assert_int_equal((int) hash[14], 183);
    assert_int_equal((int) hash[15], 110);
}
