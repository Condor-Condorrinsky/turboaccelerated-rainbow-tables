#ifndef TURBOACCELERATED_RAINBOW_TABLES_CHARSETS_H
#define TURBOACCELERATED_RAINBOW_TABLES_CHARSETS_H

enum CHARSETS{
    DIGITS          = 0,
    ALPHANUMERIC    = 1, // Digits, small and big letters of English alphabet
    ASCII_PRINTABLE = 2  // All ASCII printable characters, except space and '|'
};

const static char* const CHARSETS_STR[] = {
        [DIGITS]          = "DIGITS",
        [ALPHANUMERIC]    = "ALPHANUMERIC",
        [ASCII_PRINTABLE] = "ASCII_PRINTABLE"
};

// For GMP calculations
const static char* const CHARSETS_SET_SIZE_STR[] = {
        [DIGITS]          = "10",
        [ALPHANUMERIC]    = "62", // 26 letters of English alphabet * 2 (lower and upper) + digits
        [ASCII_PRINTABLE] = "93"  // ASCII printable characters except space and '|'
};

const static char* const ALPHANUMERIC_CHARS =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// Except space and pipe
const static char* const ASCII_PRINTABLE_CHARS =
        "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{}~";

#endif //TURBOACCELERATED_RAINBOW_TABLES_CHARSETS_H
