#include "TableMetadata.h"

void init_TableMetadata(TableMetadata* t, int chain_l, int chars){
    t->chain_len = chain_l;
    t->charset = chars;
}
