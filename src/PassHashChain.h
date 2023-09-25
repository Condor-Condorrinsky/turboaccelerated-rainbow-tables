#include <stdlib.h>
#include "reduction.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_PASSHASHCHAIN_H
#define TURBOACCELERATED_RAINBOW_TABLES_PASSHASHCHAIN_H

/*
 * A pseudo-class for convenient rainbow chain storage
 * (beginning password and ending reduced hash). Names and args
 * of all the methods are self-explanatory.
 */
typedef struct PassHashChain{
    char* passwd;
    char* end;
} PassHashChain;

PassHashChain* newChain();

char* getChainPasswd(const PassHashChain* c);

void setChainPasswd(PassHashChain* c, char* new_pass);

char* getChainEnd(const PassHashChain* c);

void setChainEnd(PassHashChain* c, char* new_end);

void deleteChain(PassHashChain* c);

#endif //TURBOACCELERATED_RAINBOW_TABLES_PASSHASHCHAIN_H
