#include <string.h>
#include "md5calc.h"

#ifndef TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H
#define TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H

void reduce(const unsigned char* digest, char* output, const char* reduction_pattern);

#endif //TURBOACCELERATED_RAINBOW_TABLES_REDUCTION_H
