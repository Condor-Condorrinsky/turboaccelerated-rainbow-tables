#include "tablelookup.h"

void lookup(FILE* rainbow_file, const char* looked_hash){
    long rainbow_size;
    unsigned long long counter = 0;
    char* rainbow_table;
    int rainbow_lines;
    PassHashChain* extracted_hashes;
    PassHashChain* extracted_copy;

    rainbow_size = get_file_size(rainbow_file);
    printf("Got file size...\n");
    rainbow_table = malloc(sizeof(char) * (rainbow_size + 1));
    load_file(rainbow_file, rainbow_table, rainbow_size);
    rainbow_table[rainbow_size] = '\0';
    printf("Loaded file into memory...\n");

    rainbow_lines = count_lines(rainbow_file);
    // https://stackoverflow.com/questions/15397728/c-pointer-to-array-of-pointers-to-structures-allocation-deallocation-issues
    extracted_hashes = malloc(rainbow_lines * sizeof(PassHashChain));
    extracted_copy = extracted_hashes;
    extract_hashed_vals(rainbow_table, &extracted_hashes);
    printf("Extracted hashes from the rainbow table...\n");

    find_hash(&extracted_hashes, rainbow_lines, looked_hash);

    free(rainbow_table);
    free(extracted_hashes);
}

void extract_hashed_vals(char* complete_table, PassHashChain** extracted_table){
    char* token;
    char* token_saved;
    unsigned long counter = 0; // which token we're processing

    // Initial setup
    token = strtok_r(complete_table, NEWLINE_STRING, &token_saved);
    line_to_PassHashChain(token, extracted_table[counter]);
    counter++;

    // Splitting
    token = strtok_r(NULL, NEWLINE_STRING, &token_saved);
    while (token != NULL){
        line_to_PassHashChain(token, extracted_table[counter]);
        token = strtok_r(NULL, NEWLINE_STRING, &token_saved);
        counter++;
    }
}

void line_to_PassHashChain(char* line, PassHashChain* c){
    char* password;
    char* hash;
    char* tok_saved;

    password = strtok_r(line, RAINBOW_TABLE_SEPARATOR, &tok_saved);
    hash = strtok_r(NULL, RAINBOW_TABLE_SEPARATOR, &tok_saved);
    setChainPasswd(c, password);
    setChainHash(c, hash);
}

void find_hash(PassHashChain** table, int entries, const char* looked_hash){
    unsigned char raw_hash[MD5_DIGEST_LENGTH];
    char raw_hash_reduced[MAX_REDUCED_PASS_LENGTH];
    char looked_hash_copy[HASH_STRING_MIN_LEN];
    unsigned char looked_hash_raw_copy[MD5_DIGEST_LENGTH];
    PassHashChain** table_ptr_copy = table;
    int pattern_counter = 0;

    safer_strncpy(looked_hash_copy, looked_hash, sizeof looked_hash_copy);
    convert_string_to_md5(looked_hash, looked_hash_raw_copy, sizeof looked_hash_raw_copy);

    for (int i = 0; i < REDUCTION_PATTERNS_SIZE; i++) {
        for (int j = 0; j < entries; j++) {
            if (strcmp(looked_hash_copy, getChainHash(*table_ptr_copy)) == 0){
                printf("Found looked_hash in chain ending with %s\n", getChainHash(*table_ptr_copy));
                hash(getChainPasswd(*table_ptr_copy), raw_hash, sizeof raw_hash);
                reduce_hash(raw_hash, raw_hash_reduced,
                            REDUCTION_PATTERN_VALUES[pattern_counter], sizeof raw_hash_reduced);
                pattern_counter++;
                while (strcmp(raw_hash_reduced, looked_hash) != 0){
                    hash(raw_hash_reduced, raw_hash, sizeof raw_hash);
                    reduce_hash(raw_hash, raw_hash_reduced,
                                REDUCTION_PATTERN_VALUES[pattern_counter], sizeof raw_hash_reduced);
                    pattern_counter++;
                }
                printf("Password: %s\n", raw_hash_reduced);
                return;
            }
            table_ptr_copy++;
        }
        reduce_and_hash(looked_hash_raw_copy, looked_hash_raw_copy,
                        sizeof looked_hash_raw_copy, REDUCTION_PATTERN_VALUES[i]);
        convert_md5_to_string(looked_hash_raw_copy, looked_hash_copy, sizeof looked_hash_copy);
        table_ptr_copy = table;
    }
}
