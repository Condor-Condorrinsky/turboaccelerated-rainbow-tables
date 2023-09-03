#include "md5calc.h"

unsigned int compute_md5(const char* input, unsigned char* digest, unsigned int digest_len){
    unsigned int written;

    if (digest_len < MD5_DIGEST_LENGTH){
        fprintf(stderr, "Digest length buffer overflow");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX* md5ctx = EVP_MD_CTX_new();
    EVP_DigestInit(md5ctx, EVP_md5());
    EVP_DigestUpdate(md5ctx, input, strlen(input));
    EVP_DigestFinal_ex(md5ctx, digest, &written);
    EVP_MD_CTX_free(md5ctx);
    return written;
}

void convert_md5_to_string(const unsigned char* input, char* output, unsigned int output_len){

    if (output_len < HASH_STRING_MIN_LEN){
        fprintf(stderr, "Output length buffer overflow");
        exit(EXIT_FAILURE);
    }

    snprintf(output, MAX_BYTE_TO_HEX_STR_LENGTH, "0x");

    char* ptr = &output[HASH_START];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++){
        ptr += snprintf(ptr, MAX_BYTE_TO_HEX_STR_LENGTH, "%02X", input[i]);
    }
}

void convert_string_to_md5(const char* input, unsigned char* output, unsigned int output_len){
    const int HEX_BASE = 16;
    const int BYTE_LEN = 2;
    char* ptr = (char*) input + HASH_START;
    char byte_buf[MAX_BYTE_TO_HEX_STR_LENGTH];

    if (output_len < MD5_DIGEST_LENGTH){
        fprintf(stderr, "Output length buffer overflow");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        memcpy(byte_buf, ptr, BYTE_LEN);
        byte_buf[MAX_BYTE_TO_HEX_STR_LENGTH - 1] = '\0';
        output[i] = (unsigned char) strtol(byte_buf, NULL, HEX_BASE);
        ptr += BYTE_LEN;
    }
}
