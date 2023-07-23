#include "stdint.h"
#include "openssl/types.h"
#include "openssl/evp.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
#define TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H

#define EVP_DIGEST_UPDATE_NUM_BYTES 1024

uint32_t compute_md5(const char* input, unsigned char digest[EVP_MAX_MD_SIZE]);

#endif //TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
