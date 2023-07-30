#include "md5_calc.h"

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
    char* ptr = &output[0];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++){
        ptr += sprintf(ptr, "%02X", output[i]);
    }
}

void print_hash(const unsigned char* input){
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        printf("%02x", input[i]);
    }
    printf("\n");
}
