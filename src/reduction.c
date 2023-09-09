#include "reduction.h"

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
