#include "tablelookup.h"

void lookup(FILE* rainbow_file){
    const long EXTRACTED_SIZE_COEFFICIENT = 2;
    const long EXTRACTED_SAFETY_BUFFER = 1024 * 10;
    long rainbow_size;
    char* rainbow_table;
    char* extracted_reduced_hashes;
    char* token;
    char* token_saved;

    rainbow_size = get_file_size(rainbow_file);
    rainbow_table = malloc(sizeof(char) * (rainbow_size + 1));
    load_file(rainbow_file, rainbow_table, rainbow_size);
    rainbow_table[rainbow_size] = '\0';

    extracted_reduced_hashes =
            malloc(((sizeof(char) * rainbow_size) / EXTRACTED_SIZE_COEFFICIENT) + EXTRACTED_SAFETY_BUFFER);
    extract_reduced_vals(rainbow_table, extracted_reduced_hashes);

    token = strtok_r(extracted_reduced_hashes, NEWLINE_STRING, &token_saved);
    while (token != NULL){

        token = strtok_r(NULL, NEWLINE_STRING, &token_saved);
    }

    free(rainbow_table);
    free(extracted_reduced_hashes);
}

void extract_reduced_vals(char* complete_table, char* extracted_table){
    char* token;
    char* token_saved;
    unsigned long counter = 3; // which token we're processing

    // Initial setup
    strtok_r(complete_table, LOOKUP_DELIMS, &token_saved);
    token = strtok_r(NULL, LOOKUP_DELIMS, &token_saved);
    safer_strncpy(extracted_table, token, strlen(token) + 1);
    strcat(extracted_table, NEWLINE_STRING);

    // Splitting
    token = strtok_r(NULL, LOOKUP_DELIMS, &token_saved);
    while (token != NULL){
        if (counter % 2 == 0){
            strcat(extracted_table, token);
            strcat(extracted_table, NEWLINE_STRING);
        }
        token = strtok_r(NULL, LOOKUP_DELIMS, &token_saved);
        counter++;
    }
}

void perform_chain_lookup(char* loaded_reduced, unsigned char md5hash[MD5_DIGEST_LENGTH]){
    char intermediate[MAX_REDUCED_PASS_LENGTH];
    unsigned char hash_result[MD5_DIGEST_LENGTH];

    memcpy(hash_result, md5hash, MD5_DIGEST_LENGTH);

    for (int i = (int) (REDUCTION_PATTERNS_SIZE - 1); i > (-1); i--) {
        for (int j = i; j < REDUCTION_PATTERNS_SIZE - 1; j++) {
            reduce_and_hash(hash_result, hash_result,
                            sizeof hash_result, sizeof hash_result,
                            REDUCTION_PATTERN_VALUES[j]);
        }
        reduce_hash(hash_result, intermediate,
                    REDUCTION_PATTERN_VALUES[REDUCTION_PATTERNS_SIZE - 1],
                    sizeof intermediate);

        if (strcmp(intermediate, loaded_reduced) == 0) {
            printf("Found hash at iteration i: %d for chain ending with %s\n", i, loaded_reduced);
            return;
        }
    }
}
