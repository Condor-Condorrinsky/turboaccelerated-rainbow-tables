#include "tablegen.h"

void generate_rainbow_table(FILE* in, FILE* out){
    long fsize;
    char* tok_saved;
    if ((fsize = get_file_size(in)) < 0){
        fprintf(stderr, "Can't open input file, aborting");
        exit(EXIT_FAILURE);
    }
    char* passes = malloc(sizeof(char) * (fsize + 1));
    unsigned char final_hash[MD5_DIGEST_LENGTH];
    char hash_string[HASH_STRING_MIN_LEN];

    load_file(in, passes, sizeof(char) * (fsize + 1));
    passes[fsize] = '\0';

    char* token = strtok_r(passes, NEWLINE_STRING, &tok_saved);
    while (token != NULL){
        generate_chain(token, final_hash, strlen(token),
                       sizeof final_hash, REDUCTION_PATTERNS_SIZE);
        convert_md5_to_string(final_hash, hash_string, sizeof hash_string);
        write_line(out, token, hash_string);
        token = strtok_r(NULL, NEWLINE_STRING, &tok_saved);
    }
    free(passes);
}

void generate_chain(const char* passwd, unsigned char* endrslt, unsigned int passwd_len, unsigned int endrslt_len,
                    unsigned int iterations){
    char rslt[MAX_REDUCED_PASS_LENGTH];

    for (int i = REDUCTION_PATTERN0; i < iterations; i++) {
        hash_and_reduce(passwd, rslt, passwd_len, sizeof rslt,
                        REDUCTION_PATTERN_VALUES[i]);
    }
    hash(rslt, endrslt, strlen(rslt), endrslt_len);
}

void hash_and_reduce(const char* input, char* output, unsigned int input_len, unsigned int output_len,
                     const char* reduction_pattern){
    unsigned char digest[MD5_DIGEST_LENGTH];

    compute_md5(input, digest, input_len, sizeof digest);
    reduce(digest, output, reduction_pattern, output_len);
}

void reduce_and_hash(const unsigned char input[MD5_DIGEST_LENGTH], unsigned char output[MD5_DIGEST_LENGTH],
                     unsigned int output_len, const char* reduction_pattern){
    char reduced[MAX_REDUCED_PASS_LENGTH];

    reduce(input, reduced, reduction_pattern, output_len);
    compute_md5(reduced, output, sizeof reduced, output_len);
}

void hash(const char* input, unsigned char* digest, unsigned int input_len, unsigned int digest_len){
    compute_md5(input, digest, input_len, digest_len);
}

void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len){
    reduce(digest, output, reduction_pattern, output_len);
}
