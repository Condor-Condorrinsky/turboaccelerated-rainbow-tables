#include "stdint.h"
#include "openssl/types.h"
#include "openssl/evp.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
#define TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H

#define MD5_DIGEST_LENGTH           16
#define EVP_DIGEST_UPDATE_NUM_BYTES 64

unsigned int compute_md5(const char* input, unsigned char digest[MD5_DIGEST_LENGTH]);
void print_hash(const unsigned char* input);

#endif //TURBOACCELERATED_RAINBOW_TABLES_MD5_CALC_H
