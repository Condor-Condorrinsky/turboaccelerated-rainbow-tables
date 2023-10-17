#include "charsets.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_TABLEMETADATA_H
#define TURBOACCELERATED_RAINBOW_TABLES_TABLEMETADATA_H

typedef struct TableMetadata{
    int chain_len;
    int passwd_len;
    int charset;
} TableMetadata;

const int DEFAULT_CHAIN_LEN  = 32;
const int DEFAULT_PASSWD_LEN = 8;
const int DEFAULT_CHARSET    = DIGITS;

void init_TableMetadata(TableMetadata* t, int chain_l, int passwd_l, int chars);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLEMETADATA_H
