#include "md5calc.h"

unsigned int compute_md5(const char* input, unsigned char* digest){
    unsigned int written;
    EVP_MD_CTX* md5ctx = EVP_MD_CTX_new();
    EVP_DigestInit(md5ctx, EVP_md5());
    EVP_DigestUpdate(md5ctx, input, EVP_DIGEST_UPDATE_NUM_BYTES);
    EVP_DigestFinal_ex(md5ctx, digest, &written);
    EVP_MD_CTX_free(md5ctx);
    return written;
}

void convert_to_string(const unsigned char* input, char* output){
    // one byte -> 2 hex digits plus null terminator
    const int MAX_BYTE_TO_HEX_STR_LENGTH = 3;

    char* ptr = &output[0];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++){
        ptr += snprintf(ptr, MAX_BYTE_TO_HEX_STR_LENGTH, "%02X", input[i]);
    }
}

void print_hash(const unsigned char* input){
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        printf("%02x", input[i]);
    }
    printf("\n");
}
