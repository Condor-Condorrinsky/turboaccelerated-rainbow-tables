#include "md5_calc.h"

uint32_t compute_md5(const char* input, unsigned char digest[EVP_MAX_MD_SIZE]){
    uint32_t written;
    EVP_MD_CTX* md5ctx = EVP_MD_CTX_new();
    EVP_DigestInit(md5ctx, EVP_md5());
    EVP_DigestUpdate(md5ctx, input, EVP_DIGEST_UPDATE_NUM_BYTES);
    EVP_DigestFinal_ex(md5ctx, digest, &written);
    EVP_MD_CTX_free(md5ctx);
    return written;
}
