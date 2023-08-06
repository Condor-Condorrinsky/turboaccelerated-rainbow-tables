#include "reduction.h"

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern){
    const int BASE_10_IDENTIFIER = 10;
    const char PATTERN_DELIMITER = '_';
    // Max 16 2-digit numbers plus 15 delimiters
    char pattern_copy[2 * MD5_DIGEST_LENGTH + 15];
    unsigned char pattern_tokenized[MD5_DIGEST_LENGTH];

    // Performing copy since strtok() modifies original string
    strcpy(pattern_copy, reduction_pattern);

    // Extract the first token
    char* token = strtok(pattern_copy, &PATTERN_DELIMITER);

    // Loop through the string to extract all other tokens
    // This variable also gives us info about how many elements are in the pattern
    int i = 0;
    while (token != NULL){
        if (i > MD5_DIGEST_LENGTH - 1) break;
        // Converting token to number, clang suggests strtol() instead of atoi()
        pattern_tokenized[i] = (unsigned char) strtol(token, NULL, BASE_10_IDENTIFIER);
        token = strtok(NULL, &PATTERN_DELIMITER);
        i++;
    }

    // Final conversion from bytes of hash to letters
    for (int j = 0; j < i; j++){
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
