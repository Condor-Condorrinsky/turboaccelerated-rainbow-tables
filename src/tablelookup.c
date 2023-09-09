#include "tablelookup.h"

int lookup(FILE* rainbow_file, const char* looked_hash){
    long size;
    char* rainbow_table;
    unsigned int entries;
    PassHashChain** extracted_hashes;
    int result;

    size = get_file_size(rainbow_file);
    printf("Got file size...\n");

    rainbow_table = malloc(sizeof(char) * (size + 1));
    load_file(rainbow_file, rainbow_table, size);
    rainbow_table[size] = '\0';
    printf("Loaded file into memory...\n");

    entries = count_lines(rainbow_file);
    printf("Found %u entries...\n", entries);

    // https://stackoverflow.com/questions/15397728/c-pointer-to-array-of-pointers-to-structures-allocation-deallocation-issues
    extracted_hashes = malloc(entries * sizeof extracted_hashes);
    for (int i = 0; i < entries; i++) {
        extracted_hashes[i] = newChain();
    }
    extract_hashed_vals(rainbow_table, extracted_hashes);
    printf("Extracted hashes from the rainbow table...\n");

    result = find_hash(extracted_hashes, entries, looked_hash);
    printf("Look up finished\n");
    if (result == 1) printf("Hash look up encountered an error, the table may be malformed\n");
    if (result == 2) printf("Hash not found in the table\n");

    for (int i = 0; i < entries; i++) {
        deleteChain(extracted_hashes[i]);
    }
    free(rainbow_table);
    free(extracted_hashes);

    return result;
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

int find_hash(PassHashChain** table, unsigned int entries, const char* looked_hash){
    unsigned char looked_hash_raw_copy[MD5_DIGEST_LENGTH];
    char looked_hash_working_copy[HASH_STRING_MIN_LEN];
    char looked_hash_reduced[MAX_REDUCED_PASS_LENGTH];
    int found = HASH_NOT_PRESENT;

    convert_string_to_md5(looked_hash, looked_hash_raw_copy, sizeof looked_hash_raw_copy);
    safer_strncpy(looked_hash_working_copy, looked_hash, sizeof looked_hash_working_copy);

    for (int i = REDUCTION_PATTERN0; i < REDUCTION_PATTERNS_SIZE; i++) {
        for (int j = 0; j < entries; j++) {
            if (strcmp(getChainHash(table[j]), looked_hash_working_copy) == 0){
                found = find_hash_in_chain(table[j], looked_hash);
            }
        }
        reduce_hash(looked_hash_raw_copy, looked_hash_reduced,
                    REDUCTION_PATTERN_VALUES[i], sizeof looked_hash_reduced, GEN_TABLE_PASS_LEN);
        hash(looked_hash_reduced, looked_hash_raw_copy, sizeof looked_hash_reduced);
        convert_md5_to_string(looked_hash_raw_copy, looked_hash_working_copy,
                              sizeof looked_hash_working_copy);
    }

    for (int k = 0; k < entries; k++) {
        if (strcmp(getChainHash(table[k]), looked_hash_working_copy) == 0){
            found = find_hash_in_chain(table[k], looked_hash);
        }
    }

    return found;
}

int find_hash_in_chain(const PassHashChain* const c, const char* hash_to_find){
    char reduced[MAX_REDUCED_PASS_LENGTH];
    unsigned char raw_hash[MD5_DIGEST_LENGTH];
    char hash_string[HASH_STRING_MIN_LEN];

    safer_strncpy(reduced, getChainPasswd(c), sizeof reduced);

    for (int i = REDUCTION_PATTERN0; i < REDUCTION_PATTERNS_SIZE; i++) {
        hash(reduced, raw_hash, sizeof raw_hash);
        convert_md5_to_string(raw_hash, hash_string, sizeof hash_string);
        if (strcmp(hash_string, hash_to_find) == 0){
            printf("------------------------------Password: %s------------------------------\n", reduced);
            return HASH_FOUND;
        }
        reduce_hash(raw_hash, reduced,
                    REDUCTION_PATTERN_VALUES[i], sizeof hash_string, GEN_TABLE_PASS_LEN);
    }

    hash(reduced, raw_hash, sizeof raw_hash);
    convert_md5_to_string(raw_hash, hash_string, sizeof hash_string);
    if (strcmp(hash_string, hash_to_find) == 0){
        printf("------------------------------Password: %s------------------------------\n", reduced);
        return HASH_FOUND;
    }

    return HASH_NOT_FOUND;
}
