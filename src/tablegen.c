#include "tablegen.h"

void generate_rainbow_table(FILE* in, FILE* out, TableMetadata* meta){
    long fsize;
    char* tok_saved;
    if ((fsize = get_file_size(in)) < 0){
        fprintf(stderr, "Can't open input file, aborting\n");
        exit(EXIT_FAILURE);
    }
    char* passes = malloc(sizeof(char) * (fsize + 1));
    char final[MAX_REDUCED_PASS_LENGTH];
    unsigned int cntr = 0;

    load_file(in, passes, sizeof(char) * (fsize + 1));

    write_metadata(out, meta);

    char* token = strtok_r(passes, NEWLINE_STRING, &tok_saved);
    while (token != NULL){
        generate_chain(token, final,
                       sizeof final, meta->chain_len);
        write_line(out, token, final);
        token = strtok_r(NULL, NEWLINE_STRING, &tok_saved);
        cntr++;
        printf("Generated chain nr %u\n", cntr);
    }
    free(passes);
}

void generate_chain(const char* passwd, char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations){
    int buf_len;
    char rslt[MAX_REDUCED_PASS_LENGTH];
    unsigned char digest[MD5_DIGEST_LENGTH];

    safer_strncpy(rslt, passwd, sizeof rslt);

    for (int i = 0; i < iterations; i++) {
        buf_len = snprintf(NULL, 0, "%d", i);
        char iter_str[buf_len + 1];
        snprintf(iter_str, buf_len, "%d", i);
        hash(rslt, digest, sizeof digest);
        reduce_hash(digest, rslt, iter_str, sizeof rslt, GEN_TABLE_PASS_LEN);
    }
    safer_strncpy(endrslt, rslt, endrslt_len);
}

void generate_chain_verbose(const char* passwd, char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations){
    int buf_len;
    char rslt[MAX_REDUCED_PASS_LENGTH];
    unsigned char digest[MD5_DIGEST_LENGTH];
    char digest_string[HASH_STRING_MIN_LEN];

    safer_strncpy(rslt, passwd, sizeof rslt);
    printf("Input: %s\n", rslt);

    for (int i = 0; i < iterations; i++) {
        buf_len = snprintf(NULL, 0, "%d", i);
        char iter_str[buf_len + 1];
        snprintf(iter_str, buf_len, "%d", i);
        hash(rslt, digest, sizeof digest);
        convert_md5_to_string(digest, digest_string, sizeof digest_string);
        printf("Hash: %s\n", digest_string);
        reduce_hash(digest, rslt, iter_str, sizeof rslt, GEN_TABLE_PASS_LEN);
        printf("Reduced: %s\n", rslt);
    }
    safer_strncpy(endrslt, rslt, endrslt_len);
    printf("Final reduced: %s\n", endrslt);
}

void hash(const char* input, unsigned char* digest, unsigned int digest_len){
    compute_md5(input, digest, digest_len);
}

void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len,
                 unsigned int reduced_pass_len){
    R(digest, output, output_len, reduction_pattern);
}
