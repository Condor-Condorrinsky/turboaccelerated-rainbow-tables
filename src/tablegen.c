#include "tablegen.h"

void generate_rainbow_table(FILE* in, FILE* out){
    long fsize;
    char* tok_saved;
    if ((fsize = get_file_size(in)) < 0){
        fprintf(stderr, "Can't open input file, aborting\n");
        exit(EXIT_FAILURE);
    }
    char* passes = malloc(sizeof(char) * (fsize + 1));
    unsigned char final_hash[MD5_DIGEST_LENGTH];
    char hash_string[HASH_STRING_MIN_LEN];

    load_file(in, passes, sizeof(char) * (fsize + 1));
    passes[fsize] = '\0';

    char* token = strtok_r(passes, NEWLINE_STRING, &tok_saved);
    while (token != NULL){
        generate_chain(token, final_hash,
                       sizeof final_hash, REDUCTION_PATTERNS_SIZE);
        convert_md5_to_string(final_hash, hash_string, sizeof hash_string);
        write_line(out, token, hash_string);
        token = strtok_r(NULL, NEWLINE_STRING, &tok_saved);
    }
    free(passes);
}

void generate_chain(const char* passwd, unsigned char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations){
    char rslt[MAX_REDUCED_PASS_LENGTH];
    unsigned char digest[MD5_DIGEST_LENGTH];

    safer_strncpy(rslt, passwd, sizeof rslt);

    for (int i = REDUCTION_PATTERN0; i < iterations; i++) {
        hash(rslt, digest, sizeof digest);
        reduce_hash(digest, rslt, REDUCTION_PATTERN_VALUES[i], sizeof rslt, GEN_TABLE_PASS_LEN);
    }
    hash(rslt, endrslt, endrslt_len);
}

void generate_chain_verbose(const char* passwd, unsigned char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations){
    char rslt[MAX_REDUCED_PASS_LENGTH];
    unsigned char digest[MD5_DIGEST_LENGTH];
    char digest_string[HASH_STRING_MIN_LEN];

    safer_strncpy(rslt, passwd, sizeof rslt);
    printf("Input: %s\n", rslt);

    for (int i = REDUCTION_PATTERN0; i < iterations; i++) {
        hash(rslt, digest, sizeof digest);
        convert_md5_to_string(digest, digest_string, sizeof digest_string);
        printf("Hash: %s\n", digest_string);
        reduce_hash(digest, rslt, REDUCTION_PATTERN_VALUES[i], sizeof rslt, GEN_TABLE_PASS_LEN);
        printf("Reduced: %s\n", rslt);
    }
    hash(rslt, endrslt, endrslt_len);
    convert_md5_to_string(endrslt, digest_string, sizeof digest_string);
    printf("Final hash: %s\n", digest_string);
}

void hash(const char* input, unsigned char* digest, unsigned int digest_len){
    compute_md5(input, digest, digest_len);
}

void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len,
                 unsigned int reduced_pass_len){
    R(digest, output, output_len, reduction_pattern);
}
