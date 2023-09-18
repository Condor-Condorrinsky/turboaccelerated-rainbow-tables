#include "reduction.h"

// https://crypto.stackexchange.com/questions/37832/how-to-create-reduction-functions-in-rainbow-tables
void R(const unsigned char* digest, char* output, unsigned int output_len, char* reduction_iteration){
    // 26^6 - all combinations of 6-letter passwords created from small letters of English alphabet
    char digest_str[HASH_STRING_MIN_LEN];
    unsigned int ret_string_len = strlen(SIX_LETTER_PASSES_SMALL_LETTERS_SET_SIZE_STR) + 1;
    char ret_string[ret_string_len];
    mpz_t ret;
    mpz_t SEARCH_SET_SIZE;
    mpz_t iteration;

    convert_md5_to_string(digest, digest_str, sizeof digest_str);
    // 0 means that function will discover base based on beginning of the string - 0x
    if (mpz_init_set_str(ret, digest_str, 0)){
        fprintf(stderr, "Failed to init mpz hash");
        exit(EXIT_FAILURE);
    }

    if (mpz_init_set_str(SEARCH_SET_SIZE, SIX_LETTER_PASSES_SMALL_LETTERS_SET_SIZE_STR, 10)){
        fprintf(stderr, "Failed to init mpz SET_SIZE");
        exit(EXIT_FAILURE);
    }
    if (mpz_init_set_str(iteration, reduction_iteration, 10)){
        fprintf(stderr, "Failed to init mpz iteration");
        exit(EXIT_FAILURE);
    }

    mpz_mod(ret, ret, SEARCH_SET_SIZE);
    mpz_add(ret, ret, iteration);

    gmp_snprintf(ret_string, ret_string_len, "%Zd", ret);

    mpz_clear(ret);
    mpz_clear(SEARCH_SET_SIZE);
    mpz_clear(iteration);
}

void encode(char* number, unsigned int desired_len, char* output_buf, unsigned int output_len){
    char letter[MAX_BYTE_TO_HEX_STR_LENGTH];
    char num_padded[strlen(SIX_LETTER_PASSES_SMALL_LETTERS_SET_SIZE_STR) + 1];
    unsigned char letter_num;
    unsigned long num_len;
    int counter = 0;

    letter[MAX_BYTE_TO_HEX_STR_LENGTH - 1] = '\0';
    pad_str_leading_zeroes(number, strlen(SIX_LETTER_PASSES_SMALL_LETTERS_SET_SIZE_STR),
                           num_padded, sizeof num_padded);
    num_len = strlen(num_padded);

    while (counter <= desired_len) {
        for (int i = 0; i < num_len - 1; i += MAX_BYTE_TO_HEX_STR_LENGTH - 1) {
            if (counter >= output_len || counter > desired_len) break;
            memcpy(letter, &num_padded[i], MAX_BYTE_TO_HEX_STR_LENGTH - 1);
            letter_num = (unsigned char) strtol(letter, NULL, 10);
            output_buf[counter] = unsigned_char_to_small_letter(letter_num);
            counter++;
        }
        for (int j = (int) num_len - 1; j > 0; j -= MAX_BYTE_TO_HEX_STR_LENGTH - 1) {
            if (counter >= output_len || counter > desired_len) break;
            memcpy(letter, &num_padded[j - 1], MAX_BYTE_TO_HEX_STR_LENGTH - 1);
            letter_num = (unsigned char) strtol(letter, NULL, 10);
            output_buf[counter] = unsigned_char_to_small_letter(letter_num);
            counter++;
        }
    }

    output_buf[counter-1] = '\0';
}

void pad_str_leading_zeroes(char* number, unsigned int desired_len, char* output_buf, unsigned int output_len){
    const char *PADDING = "0000000000000000000000000000000000000000000000000000000000000000";
    unsigned int num_len = strlen(number);

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

    int pad_len = (int) (desired_len - num_len);
    if (pad_len < 0) pad_len = 0; // Avoid negative length

    snprintf(output_buf, output_len, "%*.*s%s", pad_len, pad_len, PADDING, number);
}

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len,
            unsigned int reduced_pass_len){
    const int MAX_DELIMITERS_IN_PATTERN = 15;
    // Max 16 2-digit numbers plus 15 delimiters plus NULL
    char pattern_copy[2 * MD5_DIGEST_LENGTH + MAX_DELIMITERS_IN_PATTERN + 1];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];
    int pattern_elements;

    if (output_len < MAX_REDUCED_PASS_LENGTH){
        fprintf(stderr, "Output length buffer too small");
        exit(EXIT_FAILURE);
    }
    if (reduced_pass_len >= output_len){
        fprintf(stderr, "Output buffer too small for given reduced password length");
        exit(EXIT_FAILURE);
    }

    safer_strncpy(pattern_copy, reduction_pattern, sizeof pattern_copy);

    pattern_elements = split_by_underscores(pattern_copy, pattern_tokenized, sizeof pattern_tokenized);
    if (pattern_elements < 1){
        fprintf(stderr, "Failed to split reduction pattern");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < reduced_pass_len; i++){
        if (pattern_tokenized[i] > MD5_DIGEST_LENGTH - 1) pattern_tokenized[i] = MD5_DIGEST_LENGTH - 1;
        output[i] = unsigned_char_to_small_letter(digest[pattern_tokenized[i]]);
    }
    output[reduced_pass_len] = '\0';
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

int split_by_underscores(char* input, unsigned char* result, unsigned int result_len){
    const int BASE_10_IDENTIFIER = 10;
    const char* PATTERN_DELIMITER = "_";
    char* token;
    char* strtok_saved;

    if (result_len < MD5_DIGEST_LENGTH){
        fprintf(stderr, "Too small output buffer to split");
        return -1;
    }

    token = strtok_r(input, PATTERN_DELIMITER, &strtok_saved);

    int i = 0;
    while (token != NULL){
        if (i > MD5_DIGEST_LENGTH - 1) break;
        // Converting token to number, clang suggests strtol() instead of atoi()
        result[i] = (unsigned char) strtol(token, NULL, BASE_10_IDENTIFIER);
        token = strtok_r(NULL, PATTERN_DELIMITER, &strtok_saved);
        i++;
    }

    return i;
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
