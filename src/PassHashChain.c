#include "PassHashChain.h"

PassHashChain* newChain(){
    PassHashChain* c = malloc(sizeof(PassHashChain));
    if (c == NULL) return NULL;

    c->passwd = malloc(sizeof(char) * MAX_REDUCED_PASS_LENGTH);
    if (c->passwd == NULL){
        free(c);
        return NULL;
    }

    c->end = malloc(sizeof(char) * MAX_REDUCED_PASS_LENGTH);
    if (c->end == NULL){
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

char* getChainEnd(const PassHashChain* c){
    return c->end;
}

void setChainEnd(PassHashChain* c, char* new_end){
    safer_strncpy(c->end, new_end, MAX_REDUCED_PASS_LENGTH);
}

void deleteChain(PassHashChain* c){
    if (c != NULL){
        free(c->passwd);
        free(c->end);
        free(c);
    }
}
