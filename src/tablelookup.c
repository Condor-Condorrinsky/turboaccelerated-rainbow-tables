#include "tablelookup.h"

int lookup(FILE* rainbow_file, const char* looked_hash){
    long size;
    char* rainbow_table;
    char set_size[SET_SIZE_BUFFER];
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

    calc_set_size(strlen(extracted_hashes[0]->passwd), DIGITS, set_size, sizeof set_size);

    result = find_hash(extracted_hashes, entries, looked_hash, set_size);
    printf("Look up finished\n");
    if (result == HASH_NOT_FOUND)
        printf("There appears to be too many collisions in table, hash couldn't be found\n");
    if (result == HASH_NOT_PRESENT)
        printf("Hash not found in the table\n");

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
    setChainEnd(c, hash);
}

int find_hash(PassHashChain** table, unsigned int entries, const char* looked_hash, const char* set_size){
    unsigned char looked_hash_raw_copy[MD5_DIGEST_LENGTH];
    char looked_hash_working_copy[HASH_STRING_MIN_LEN];
    char looked_hash_reduced[MAX_REDUCED_PASS_LENGTH];
    char iter_str[SET_SIZE_BUFFER];
    int found = HASH_NOT_FOUND;

    for (int i = (int) REDUCTION_PATTERNS_SIZE - 1; i > -1 ; i--) {
        for (int j = i; j < REDUCTION_PATTERNS_SIZE; j++){
            iter_itoa(j, iter_str, sizeof iter_str);
            reduce_hash(looked_hash_raw_copy, looked_hash_reduced,
                        iter_str, sizeof looked_hash_raw_copy,
                        set_size, strlen(table[0]->passwd));
            hash(looked_hash_reduced, looked_hash_raw_copy, sizeof looked_hash_raw_copy);
            convert_md5_to_string(looked_hash_raw_copy, looked_hash_working_copy,
                                  sizeof looked_hash_working_copy);
        }
        for (int j = 0; j < entries; j++) {
            if (strcmp(looked_hash_reduced, getChainEnd(table[j])) == 0){
                printf("Found possible match in chain nr i=%d, j=%d\n", i, j);
                printf("Chain password: %s, chain end: %s\n", getChainPasswd(table[j]), getChainEnd(table[j]));
                found = find_hash_in_chain(table[j], looked_hash, set_size);
                if (found == HASH_FOUND)
                    return found;
            }
        }
        convert_string_to_md5(looked_hash, looked_hash_raw_copy, sizeof looked_hash_raw_copy);
        safer_strncpy(looked_hash_working_copy, looked_hash, sizeof looked_hash_working_copy);
    }

    return found;
}

int find_hash_in_chain(const PassHashChain* const c, const char* hash_to_find, const char* set_size){
    char reduced[MAX_REDUCED_PASS_LENGTH];
    unsigned char raw_hash[MD5_DIGEST_LENGTH];
    char hash_string[HASH_STRING_MIN_LEN];
    char iter_str[SET_SIZE_BUFFER];

    safer_strncpy(reduced, getChainPasswd(c), sizeof reduced);

    for (int i = REDUCTION_PATTERN0; i < REDUCTION_PATTERNS_SIZE; i++) {
        hash(reduced, raw_hash, sizeof raw_hash);
        convert_md5_to_string(raw_hash, hash_string, sizeof hash_string);
        if (strcmp(hash_string, hash_to_find) == 0){
            printf("------------------------------Password: %s------------------------------\n", reduced);
            return HASH_FOUND;
        }
        calc_set_size(strlen(c->passwd), DIGITS, iter_str, sizeof iter_str);
        reduce_hash(raw_hash, reduced,
                    iter_str, sizeof reduced,
                    set_size, strlen(c->passwd));
    }

    hash(reduced, raw_hash, sizeof raw_hash);
    convert_md5_to_string(raw_hash, hash_string, sizeof hash_string);
    if (strcmp(hash_string, hash_to_find) == 0){
        printf("------------------------------Password: %s------------------------------\n", reduced);
        return HASH_FOUND;
    }

    return HASH_NOT_FOUND;
}

int str_to_uppercase(const char* input, char* output, unsigned int output_len){
    unsigned int input_len = strlen(input);
    if (input_len + 1 > output_len){
        fprintf(stderr, "Cannot convert to uppercase; buffer too small\n");
        return EXIT_FAILURE;
    }
    for (unsigned int i = 0; i < input_len; i++) {
        output[i] = (char) toupper(input[i]);
    }
    output[output_len] = '\0';
    return EXIT_SUCCESS;
}
