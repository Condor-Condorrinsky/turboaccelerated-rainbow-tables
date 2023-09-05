#include <stdlib.h>
#include "reduction.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_PASSHASHCHAIN_H
#define TURBOACCELERATED_RAINBOW_TABLES_PASSHASHCHAIN_H

/*
 * A pseudo-class for convenient rainbow chain storage
 * (beginning password and ending hash). Names and args
 * of all the methods are self-explanatory.
 */
typedef struct PassHashChain{
    char* passwd;
    char* hash;
} PassHashChain;

PassHashChain* newChain();

char* getChainPasswd(const PassHashChain* c);

void setChainPasswd(PassHashChain* c, char* new_pass);

char* getChainHash(const PassHashChain* c);

void setChainHash(PassHashChain* c, char* new_hash);

void deleteChain(PassHashChain* c);

#endif //TURBOACCELERATED_RAINBOW_TABLES_PASSHASHCHAIN_H
