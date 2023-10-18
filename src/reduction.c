#include "reduction.h"

void R(const unsigned char* digest, char* output, unsigned int output_len, const char* reduction_iteration){
    const int DESIRED_PASS_LEN = 8;
    char digest_str[HASH_STRING_MIN_LEN];
    unsigned int ret_string_len = strlen(EIGHT_DIGIT_PINS_SET_SIZE_STR) + 1;
    char ret_string[ret_string_len];
    mpz_t ret;
    mpz_t SEARCH_SET_SIZE;
    mpz_t iteration;

    convert_md5_to_string(digest, digest_str, sizeof digest_str);
    // 0 means that function will discover base based on beginning of the string - 0x
    if (mpz_init_set_str(ret, digest_str, 0)){
        fprintf(stderr, "Failed to init mpz hash\n");
        exit(EXIT_FAILURE);
    }

    if (mpz_init_set_str(SEARCH_SET_SIZE, EIGHT_DIGIT_PINS_SET_SIZE_STR, 10)){
        fprintf(stderr, "Failed to init mpz SET_SIZE\n");
        exit(EXIT_FAILURE);
    }
    if (mpz_init_set_str(iteration, reduction_iteration, 10)){
        fprintf(stderr, "Failed to init mpz iteration\n");
        exit(EXIT_FAILURE);
    }

    mpz_add(ret, ret, iteration);
    mpz_mod(ret, ret, SEARCH_SET_SIZE);

    gmp_snprintf(ret_string, ret_string_len, "%Zd", ret);

    pad_str_leading_zeroes(ret_string, DESIRED_PASS_LEN, output, output_len);

    mpz_clear(ret);
    mpz_clear(SEARCH_SET_SIZE);
    mpz_clear(iteration);
}

// TODO: calc_R_set_size() to initialize set size for R() function
void calc_R_set_size(unsigned int pass_len, int mode, char* output, unsigned int output_len){
    const char* set_size_str;
    mpz_t set_size;
    mpz_t result;

    switch (mode) {
        case DIGITS:
            set_size_str = CHARSETS_SET_SIZE_STR[DIGITS];
            break;
        case ALPHANUMERIC:
            set_size_str = CHARSETS_SET_SIZE_STR[ALPHANUMERIC];
            break;
        case ASCII_PRINTABLE:
            set_size_str = CHARSETS_SET_SIZE_STR[ASCII_PRINTABLE];
            break;
        default:
            fprintf(stderr, "Unrecognized mode for set size calculation, aborting\n");
            exit(EXIT_FAILURE);
    }

    if (mpz_init_set_str(set_size, set_size_str, 10)){
        fprintf(stderr, "Failed to init mpz set size in calc_R_set_size()\n");
        exit(EXIT_FAILURE);
    }
    if (mpz_init_set_str(result, set_size_str, 10)){
        fprintf(stderr, "Failed to init mpz ret in calc_R_set_size()\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < pass_len; i++) {
        mpz_mul(result, result, set_size);
    }
    gmp_snprintf(output, output_len, "%Zd", result);

    mpz_clear(set_size);
    mpz_clear(result);
}

void pad_str_leading_zeroes(char* number, unsigned int desired_len, char* output_buf, unsigned int output_len){
    const char *PADDING = "0000000000000000000000000000000000000000000000000000000000000000";
    unsigned int num_len = strlen(number);
    char number_copy[num_len + 1];

    if (output_len < desired_len + 1){
        fprintf(stderr,
                "Output buffer is too small for desired length, padding was not performed\n");
        exit(EXIT_FAILURE);
    }
    if (num_len + 1 > output_len){
        fprintf(stderr,
                "Specified buffer is too small for given number, padding was skipped\n");
        exit(EXIT_FAILURE);
    }

    safer_strncpy(number_copy, number, num_len + 1);

    int pad_len = (int) (desired_len - num_len);
    if (pad_len < 0) {
        fprintf(stderr, "ERROR: passwords longer than 64 chars are not supported, aborting\n");
        exit(EXIT_FAILURE);
    }

    snprintf(output_buf, output_len, "%*.*s%s", pad_len, pad_len, PADDING, number_copy);
}

char* safer_strncpy(char* dest, const char* src, size_t n){
    strncpy(dest, src, n);
    dest += n - 1;
    if (*dest != '\0') {
        fprintf(stderr, "safer_strncpy detected overflow for string %s, swapping last byte to \\0\n", src);
        *dest = '\0';
    }
    dest -= n - 1;
    return dest;
}

char unsigned_char_to_ascii(const unsigned char in){
    const unsigned char ASCII_BEGINNING_PRINTABLE_CHARS = 33;
    const unsigned char ASCII_PRINTABLE_CHARS_NO_SPACE = 93;
    const unsigned char ASCII_PIPELINE = 124;
    const unsigned char ASCII_EXCLAMATION_MARK = 33;

    char ret = (char) ((in % ASCII_PRINTABLE_CHARS_NO_SPACE) + ASCII_BEGINNING_PRINTABLE_CHARS);
    if (ret == ASCII_PIPELINE) ret = (char) ASCII_EXCLAMATION_MARK;

    return ret;
}

char unsigned_char_to_small_letter(const unsigned char in){
    const unsigned char LETTERS_IN_ENGLISH_ALPHABET = 26;
    const unsigned char ASCII_LETTER_SMALL_A = 97;

    return (char) ((in % LETTERS_IN_ENGLISH_ALPHABET) + ASCII_LETTER_SMALL_A);
}
