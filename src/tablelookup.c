#include "tablelookup.h"

void lookup(FILE* rainbow_file){
    long rainbow_size;
    char* rainbow_table;

    rainbow_size = get_file_size(rainbow_file);
    rainbow_table = malloc(sizeof(char) * (rainbow_size + 1));
    rainbow_table[rainbow_size] = '\0';


}

void extract_reduced_vals(char* rainbow_buf){
    // const char* NEWLINE_DELIM = "\n";
    // const char* RAINBOW_DELIM = RAINBOW_TABLE_SEPARATOR;
    char DELIMITERS[6];
    strcpy(DELIMITERS, "\n");
    strcat(DELIMITERS, RAINBOW_TABLE_SEPARATOR);
    char* line;
    char* newline_saved;
    char* rainbow_delim_saved;

    line = strtok_r(rainbow_buf, DELIMITERS, &newline_saved);
}
