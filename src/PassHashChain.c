#include "PassHashChain.h"

PassHashChain* newChain(){
    PassHashChain* c = malloc(sizeof(PassHashChain));
    if (c == NULL) return NULL;

    c->passwd = malloc(sizeof(char) * MAX_REDUCED_PASS_LENGTH);
    if (c->passwd == NULL){
        free(c);
        return NULL;
    }

    c->hash = malloc(sizeof(char) * HASH_STRING_MIN_LEN);
    if (c->hash == NULL){
        free(c->passwd);
        free(c);
        return NULL;
    }

    return c;
}

char* getChainPasswd(const PassHashChain* c){
    return c->passwd;
}

void setChainPasswd(PassHashChain* c, char* new_pass){
    safer_strncpy(c->passwd, new_pass, MAX_REDUCED_PASS_LENGTH);
}

char* getChainHash(const PassHashChain* c){
    return c->hash;
}

void setChainHash(PassHashChain* c, char* new_hash){
    safer_strncpy(c->hash, new_hash, HASH_STRING_MIN_LEN);
}

void deleteChain(PassHashChain* c){
    if (c != NULL){
        if (c->passwd != NULL) free(c->passwd);
        if (c->hash != NULL) free(c->hash);
        free(c);
    }
}
