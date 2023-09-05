#include "tablelookup.h"

void lookup(FILE* rainbow_file, const char* hash){
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



    free(rainbow_table);
    free(extracted_hashes);
}

void extract_hashed_vals(char* complete_table, PassHashChain** extracted_table){
    char* token;
    char* token_saved;
    unsigned long counter = 1; // which token we're processing

    // Initial setup
    token = strtok_r(complete_table, NEWLINE_STRING, &token_saved);
    *extracted_table = line_to_PassHashChain(token);
    extracted_table++;

    // Splitting
    token = strtok_r(NULL, NEWLINE_STRING, &token_saved);
    while (token != NULL){
        *extracted_table = line_to_PassHashChain(token);
        extracted_table++;
        token = strtok_r(NULL, NEWLINE_STRING, &token_saved);
        counter++;
    }
}

PassHashChain* line_to_PassHashChain(char* line){
    char* password;
    char* hash;
    char* tok_saved;
    PassHashChain* ret;

    ret = newChain();
    password = strtok_r(line, RAINBOW_TABLE_SEPARATOR, &tok_saved);
    hash = strtok_r(NULL, RAINBOW_TABLE_SEPARATOR, &tok_saved);
    setChainPasswd(ret, password);
    setChainHash(ret, hash);

    return ret;
}

void find_hash(PassHashChain** table, int entries, const char* hash){
    for (int i = 0; i < REDUCTION_PATTERNS_SIZE; i++) {
        for (int j = 0; j < entries; j++) {

        }
        // reduce_and_hash();
    }
}
