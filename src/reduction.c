#include "reduction.h"

void R(const unsigned char* digest, char* output, unsigned int output_len, const char* reduction_iteration,
       const char* set_size, unsigned int pass_len){
    char digest_str[HASH_STRING_MIN_LEN];
    unsigned int ret_string_len = strlen(set_size) + 1;
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

    if (mpz_init_set_str(SEARCH_SET_SIZE, set_size, 10)){
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

    pad_str_leading_zeroes(ret_string, pass_len, output, output_len);

    mpz_clear(ret);
    mpz_clear(SEARCH_SET_SIZE);
    mpz_clear(iteration);
}

void calc_R_set_size(unsigned int pass_len, int mode, char* output, unsigned int output_len){
    unsigned int result_len;
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

    for (int i = 1; i < pass_len; i++) {
        mpz_mul(result, result, set_size);
    }

    result_len = gmp_snprintf(NULL, 0, "%Zd", result);
    if (result_len > output_len){
        fprintf(stderr,
                "Cannot pass calculated set size to buffer due to insufficient size. Required size: %u, received size: %u\n",
                result_len, output_len);
        exit(EXIT_FAILURE);
    }
    gmp_snprintf(output, output_len, "%Zd", result);

    mpz_clear(set_size);
    mpz_clear(result);
}

void encode_result(int mode, unsigned int desired_len, char* data, char* output, unsigned int output_len){
    switch (mode) {
        case DIGITS:
            pad_str_leading_zeroes(data, desired_len, output, output_len);
            break;
        case ALPHANUMERIC:
            break;
        case ASCII_PRINTABLE:
            break;
        default:
            break;
    }
}

void encode(char* number, unsigned int desired_len, int mode, char* output_buf, unsigned int output_len){
    char letter[MAX_BYTE_TO_HEX_STR_LENGTH];
    char num_padded[MAX_REDUCED_PASS_LENGTH];
    unsigned char letter_num;
    unsigned long num_len;
    int counter = 0;

    if (desired_len + 1 > output_len){
        fprintf(stderr, "Desired length bigger than output buffer, aborting\n");
        exit(EXIT_FAILURE);
    }

    letter[MAX_BYTE_TO_HEX_STR_LENGTH - 1] = '\0';
    pad_str_leading_zeroes(number, desired_len,
                           num_padded, sizeof num_padded);
    num_len = strlen(num_padded);

    while (counter < output_len && counter < desired_len) {
        for (int i = 0; i < num_len - 1; i += MAX_BYTE_TO_HEX_STR_LENGTH - 1) {
            if (counter >= output_len || counter >= desired_len) break;
            memcpy(letter, &num_padded[i], MAX_BYTE_TO_HEX_STR_LENGTH - 1);
            letter_num = (unsigned char) strtol(letter, NULL, 10);
            switch (mode) {
                case ALPHANUMERIC:
                    output_buf[counter] = uchar_to_alphanumeric(letter_num);
                    break;
                case ASCII_PRINTABLE:
                default:
                    output_buf[counter] = uchar_to_ascii(letter_num);
                    break;
            }
            counter++;
        }
        for (int j = (int) num_len - 1; j > 0; j -= MAX_BYTE_TO_HEX_STR_LENGTH - 1) {
            if (counter >= output_len || counter >= desired_len) break;
            memcpy(letter, &num_padded[j - 1], MAX_BYTE_TO_HEX_STR_LENGTH - 1);
            letter_num = (unsigned char) strtol(letter, NULL, 10);
            switch (mode) {
                case ALPHANUMERIC:
                    output_buf[counter] = uchar_to_alphanumeric(letter_num);
                    break;
                case ASCII_PRINTABLE:
                default:
                    output_buf[counter] = uchar_to_ascii(letter_num);
                    break;
            }
            counter++;
        }
    }
    output_buf[counter] = '\0';
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
        pad_len = 0;
        fprintf(stderr, "WARNING: negative pad length\n");
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

char uchar_to_alphanumeric(unsigned char in){
    unsigned char val = in % strlen(ALPHANUMERIC_CHARS);
    return ALPHANUMERIC_CHARS[val];
}

char uchar_to_ascii(unsigned char in){
    unsigned char val = in % strlen(ASCII_PRINTABLE_CHARS);
    return ASCII_PRINTABLE_CHARS[val];
}
