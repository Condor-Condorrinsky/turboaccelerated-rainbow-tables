#include "tablegen.h"

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
