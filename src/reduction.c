#include "reduction.h"

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len){
    const int MAX_DELIMITERS_IN_PATTERN = 15;
    // Max 16 2-digit numbers plus 15 delimiters plus NULL
    char pattern_copy[2 * MD5_DIGEST_LENGTH + MAX_DELIMITERS_IN_PATTERN + 1];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];
    int i;

    if (output_len < MD5_DIGEST_LENGTH + 1){
        fprintf(stderr, "Output length buffer too small");
        exit(EXIT_FAILURE);
    }

    safer_strncpy(pattern_copy, reduction_pattern, sizeof pattern_copy);

    i = split_by_underscores(pattern_copy, pattern_tokenized, sizeof pattern_tokenized);
    if (i < 1){
        fprintf(stderr, "Failed to split");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < i; j++){
        if (pattern_tokenized[j] > MD5_DIGEST_LENGTH - 1) pattern_tokenized[j] = MD5_DIGEST_LENGTH - 1;
        output[j] = unsigned_char_to_ascii(digest[pattern_tokenized[j]]);
    }
    output[i] = '\0';
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
