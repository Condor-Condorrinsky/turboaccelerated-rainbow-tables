#include "reduction.h"

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern){
    const char PATTERN_DELIMITER = '_';

    // Performing copy since strtok() modifies original string
    char pattern_copy[MD5_DIGEST_LENGTH + 1];
    strcpy(pattern_copy, reduction_pattern);

    // Extract the first token
    char* token = strtok(pattern_copy, &PATTERN_DELIMITER);
    // Loop through the string to extract all other tokens
    int i = 0;
    while( token != NULL ) {
        printf( " %s\n", token ); //printing each token
        token = strtok(NULL, &PATTERN_DELIMITER);
    }
}
