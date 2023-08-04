#include "reduction.h"

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern){
    const int BASE_10_IDENTIFIER = 10;
    const char PATTERN_DELIMITER = '_';
    char pattern_copy[MD5_DIGEST_LENGTH];
    unsigned char pattern_numbers[MD5_DIGEST_LENGTH];

    // Performing copy since strtok() modifies original string
    memcpy(pattern_copy, reduction_pattern, MD5_DIGEST_LENGTH);

    // Extract the first token
    char* token = strtok(pattern_copy, &PATTERN_DELIMITER);

    // Converting first token to number, clang suggests strtol() instead of atoi()
    pattern_numbers[0] = (unsigned char) strtol(token, NULL, BASE_10_IDENTIFIER);

    // Loop through the string to extract all other tokens, starting from 1 since token 0 is extracted
    int i = 1;
    while (token != NULL){
        if (i > MD5_DIGEST_LENGTH - 1) break;
        token = strtok(NULL, &PATTERN_DELIMITER);
        pattern_numbers[i] = (unsigned char) strtol(token, NULL, BASE_10_IDENTIFIER);
        i++;
    }


}

char unsigned_char_to_ascii(const unsigned char in){


    return 0;
}
