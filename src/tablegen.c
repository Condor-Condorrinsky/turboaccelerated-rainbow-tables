#include "tablegen.h"

void generate_rainbow_table(FILE* in, FILE* out, TableMetadata* meta){
    long fsize;
    char* tok_saved;
    if ((fsize = get_file_size(in)) < 0){
        fprintf(stderr, "Can't open input file, aborting\n");
        exit(EXIT_FAILURE);
    }
    char* passes = malloc(sizeof(char) * (fsize + 1));
    char set_size[SET_SIZE_BUFFER];
    char final[MAX_REDUCED_PASS_LENGTH];
    unsigned int pass_len;
    unsigned int cntr = 0;

    load_file(in, passes, sizeof(char) * (fsize + 1));

    write_metadata(out, meta);

    char* token = strtok_r(passes, NEWLINE_STRING, &tok_saved);
    pass_len = strlen(token);
    calc_set_size(pass_len, meta->charset, set_size, sizeof set_size);
    while (token != NULL){
        generate_chain(token, final,
                       sizeof final, meta->chain_len,
                       set_size, meta->charset);
        write_line(out, token, final);
        token = strtok_r(NULL, NEWLINE_STRING, &tok_saved);
        cntr++;
        printf("Generated chain nr %u\n", cntr);
    }
    free(passes);
}

void generate_chain(const char* passwd, char* endrslt, unsigned int endrslt_len,
                    unsigned int iterations, const char* set_size, int mode){
    char rslt[MAX_REDUCED_PASS_LENGTH];
    unsigned char digest[MD5_DIGEST_LENGTH];
    char iter_str[SET_SIZE_BUFFER];

    safer_strncpy(rslt, passwd, sizeof rslt);

    for (int i = 0; i < iterations; i++) {
        iter_itoa(i, iter_str, sizeof iter_str);
        hash(rslt, digest, sizeof digest);
        reduce_hash(digest, rslt, iter_str, sizeof rslt, set_size, strlen(passwd), mode);
    }
    safer_strncpy(endrslt, rslt, endrslt_len);
}

void iter_itoa(int i, char* buf, unsigned int buf_len){
    int req_len = snprintf(NULL, 0, "%d", i);
    if (req_len + 1 > buf_len){
        fprintf(stderr, "Too small buffer for integer to array conversion\n");
        exit(EXIT_FAILURE);
    }
    snprintf(buf, buf_len, "%d", i);
}

void hash(const char* input, unsigned char* digest, unsigned int digest_len){
    compute_md5(input, digest, digest_len);
}

void reduce_hash(const unsigned char* digest, char* output, const char* reduction_pattern, unsigned int output_len,
                 const char* set_size, unsigned int reduced_pass_len, int mode){
    R(digest, output, output_len, reduction_pattern, set_size, reduced_pass_len, mode);
}

void calc_set_size(unsigned int pass_len, int mode, char* output, unsigned int output_len){
    calc_R_set_size(pass_len, mode, output, output_len);
}
