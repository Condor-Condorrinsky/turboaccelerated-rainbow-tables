#ifndef TURBOACCELERATED_RAINBOW_TABLES_TABLEMETADATA_H
#define TURBOACCELERATED_RAINBOW_TABLES_TABLEMETADATA_H

typedef struct TableMetadata{
    int chain_len;
    int passwd_len;
    int charset;
} TableMetadata;

void init_TableMetadata(TableMetadata* t, int chain_l, int passwd_l, int chars);

#endif //TURBOACCELERATED_RAINBOW_TABLES_TABLEMETADATA_H
