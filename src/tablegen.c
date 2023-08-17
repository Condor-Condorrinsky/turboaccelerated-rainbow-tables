#include "tablegen.h"

void generate_rainbow_table(FILE* in, FILE* out){
    const char DELIMITER = '\n';
    long fsize;
    char* tok_saved;
    if ((fsize = get_file_size(in)) < 0){
        fprintf(stderr, "Can't open input file, aborting");
        exit(EXIT_FAILURE);
    }
    char passes[fsize + 1];
    char passes_copy[fsize + 1];
    char pass_reduced[MAX_PASS_LENGTH];

    load_pass_dictionary(in, passes, sizeof passes);
    passes[fsize] = '\0';

    strncpy(passes_copy, passes, fsize + 1);
    if (passes_copy[sizeof(passes_copy) - 1] != '\0') {
        // We have overflow.
        fprintf(stderr, "Reduction pattern length buffer overflow");
        exit(EXIT_FAILURE);
    }

    char* token = strtok_r(passes_copy, &DELIMITER, &tok_saved);
    while (token != NULL){
        generate_chain(token, pass_reduced,
                       sizeof passes_copy, sizeof pass_reduced, REDUCTION_PATTERNS_SIZE);
        write_line(out, token, pass_reduced);
        token = strtok_r(NULL, &DELIMITER, &tok_saved);
    }
}

void generate_chain(const char* passwd, char* endrslt, unsigned int passwd_len, unsigned int endrslt_len,
                    unsigned int iterations){
    for (int i = REDUCTION_PATTERN0; i < iterations; i++) {
        hash_and_reduce(passwd, endrslt, passwd_len, endrslt_len,
                        REDUCTION_PATTERN_VALUES[i]);
    }
}

void hash_and_reduce(const char* input, char* output, unsigned int input_len, unsigned int output_len,
                     const char* reduction_pattern){
    unsigned char digest[MD5_DIGEST_LENGTH];

    compute_md5(input, digest, input_len, sizeof digest);
    reduce(digest, output, reduction_pattern, sizeof digest, output_len);
}

void hash(const char* input, unsigned char* digest, unsigned int input_len, unsigned int digest_len){
    compute_md5(input, digest, input_len, digest_len);
}

void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern,
                 unsigned int digest_len, unsigned int output_len){
    reduce(digest, output, reduction_pattern, digest_len, output_len);
}
