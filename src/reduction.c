#include "reduction.h"

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern,
            unsigned int digest_len, unsigned int output_len){
    const int BASE_10_IDENTIFIER = 10;
    const int MAX_DELIMITERS_IN_PATTERN = 15;
    const char PATTERN_DELIMITER = '_';
    // Max 16 2-digit numbers plus 15 delimiters plus NULL
    char pattern_copy[2 * MD5_DIGEST_LENGTH + MAX_DELIMITERS_IN_PATTERN + 1];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];
    char* tok_saved;

    if (digest_len != MD5_DIGEST_LENGTH){
        fprintf(stderr, "Digest buffer is of wrong length");
        exit(EXIT_FAILURE);
    }
    if (output_len < MD5_DIGEST_LENGTH + 1){
        fprintf(stderr, "Output length buffer too small");
        exit(EXIT_FAILURE);
    }

    // Performing copy since strtok_r() modifies original string
    strncpy(pattern_copy, reduction_pattern, 2 * MD5_DIGEST_LENGTH + MAX_DELIMITERS_IN_PATTERN + 1);
    if (pattern_copy[sizeof(pattern_copy) - 1] != '\0') {
        // We have overflow.
        fprintf(stderr, "Reduction pattern length buffer overflow");
        exit(EXIT_FAILURE);
    }

    // Extract the first token
    char* token = strtok_r(pattern_copy, &PATTERN_DELIMITER, &tok_saved);

    // Loop through the string to extract all other tokens
    // This variable also gives us info about how many elements are in the pattern
    int i = 0;
    while (token != NULL){
        if (i > MD5_DIGEST_LENGTH - 1) break;
        // Converting token to number, clang suggests strtol() instead of atoi()
        pattern_tokenized[i] = (unsigned char) strtol(token, NULL, BASE_10_IDENTIFIER);
        token = strtok_r(NULL, &PATTERN_DELIMITER, &tok_saved);
        i++;
    }

    // Final conversion from bytes of hash to letters
    for (int j = 0; j < i; j++){
        // Safeguard if someone decided to tamper with our function
        if (pattern_tokenized[j] > MD5_DIGEST_LENGTH - 1) pattern_tokenized[j] = MD5_DIGEST_LENGTH - 1;
        output[j] = unsigned_char_to_ascii(digest[pattern_tokenized[j]]);
    }
    output[i] = '\0';
}

char unsigned_char_to_ascii(const unsigned char in){
    // These are small numerical values, not chars per se
    const unsigned char LETTERS_IN_ENGLISH_ALPHABET = 26;
    const unsigned char ASCII_LETTER_SMALL_A = 97;

    return (char) ((in % LETTERS_IN_ENGLISH_ALPHABET) + ASCII_LETTER_SMALL_A);
}
