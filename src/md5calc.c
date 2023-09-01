#include "md5calc.h"

unsigned int compute_md5(const char* input, unsigned char* digest, unsigned int input_len, unsigned int digest_len){
    unsigned int written;

    if (digest_len < MD5_DIGEST_LENGTH){
        fprintf(stderr, "Digest length buffer overflow");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX* md5ctx = EVP_MD_CTX_new();
    EVP_DigestInit(md5ctx, EVP_md5());
    EVP_DigestUpdate(md5ctx, input, input_len);
    EVP_DigestFinal_ex(md5ctx, digest, &written);
    EVP_MD_CTX_free(md5ctx);
    return written;
}

void convert_md5_to_string(const unsigned char* input, char* output, unsigned int output_len){
    // one byte -> 2 hex digits plus null terminator
    const int MAX_BYTE_TO_HEX_STR_LENGTH = 3;
    const int HASH_START_PRINTING = 2;

    if (output_len < HASH_STRING_MIN_LEN){
        fprintf(stderr, "Output length buffer overflow");
        exit(EXIT_FAILURE);
    }

    snprintf(output, MAX_BYTE_TO_HEX_STR_LENGTH, "0x");

    char* ptr = &output[HASH_START_PRINTING];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++){
        ptr += snprintf(ptr, MAX_BYTE_TO_HEX_STR_LENGTH, "%02X", input[i]);
    }
}
