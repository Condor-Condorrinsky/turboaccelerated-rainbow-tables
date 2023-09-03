#include "tablelookup.h"

void lookup(FILE* rainbow_file, const char* hash){
    const long EXTRACTED_SIZE_COEFFICIENT = 2;
    const long EXTRACTED_SAFETY_BUFFER = 1024 * 10;
    long rainbow_size;
    char* rainbow_table;
    char* extracted_hashes;
    char* token;
    char* token_saved;

    rainbow_size = get_file_size(rainbow_file);
    rainbow_table = malloc(sizeof(char) * (rainbow_size + 1));
    load_file(rainbow_file, rainbow_table, rainbow_size);
    rainbow_table[rainbow_size] = '\0';

    extracted_hashes =
            malloc(((sizeof(char) * rainbow_size) / EXTRACTED_SIZE_COEFFICIENT) + EXTRACTED_SAFETY_BUFFER);
    extract_hashed_vals(rainbow_table, extracted_hashes);

    token = strtok_r(extracted_hashes, NEWLINE_STRING, &token_saved);
    while (token != NULL){
        if (perform_chain_lookup(token, hash) == HASH_FOUND) {
            free(rainbow_table);
            free(extracted_hashes);
            return;
        }
        token = strtok_r(NULL, NEWLINE_STRING, &token_saved);
    }
    free(rainbow_table);
    free(extracted_hashes);
}

void extract_hashed_vals(char* complete_table, char* extracted_table){
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

int perform_chain_lookup(const char* loaded_hash, const char* md5hash){
    unsigned char hash_result[MD5_DIGEST_LENGTH];
    char hash_string[HASH_STRING_MIN_LEN];
    char reduced[MAX_REDUCED_PASS_LENGTH];

    for (int i = (int) (REDUCTION_PATTERNS_SIZE - 1); i > (-1); i--) {
        convert_string_to_md5(md5hash, hash_result, sizeof hash_result);
        for (int j = i; j < REDUCTION_PATTERNS_SIZE; j++) {
            reduce_hash(hash_result, reduced, REDUCTION_PATTERN_VALUES[j], sizeof reduced);
            hash(reduced, hash_result, sizeof hash_result);
        }
        convert_md5_to_string(hash_result, hash_string, sizeof hash_string);
        if (strcmp(hash_string, loaded_hash) == 0) {
            printf("Found hash at iteration i = %d for password = %s in chain ending with %s\n",
                   i, reduced, loaded_hash);
            return HASH_FOUND;
        }
    }
    return HASH_NOT_FOUND;
}
