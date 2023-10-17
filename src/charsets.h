#ifndef TURBOACCELERATED_RAINBOW_TABLES_CHARSETS_H
#define TURBOACCELERATED_RAINBOW_TABLES_CHARSETS_H

enum CHARSETS{
    DIGITS          = 0,
    ALPHANUMERIC    = 1, // Digits, small and big letters of English alphabet
    ASCII_PRINTABLE = 2  // All ASCII printable characters, EXCLUDING whitespace chars (spaces etc.)
};

const static char* const CHARSETS_STR[] = {
        [DIGITS]          = "DIGITS",
        [ALPHANUMERIC]    = "ALPHANUMERIC",
        [ASCII_PRINTABLE] = "ASCII_PRINTABLE"
};

#endif //TURBOACCELERATED_RAINBOW_TABLES_CHARSETS_H
