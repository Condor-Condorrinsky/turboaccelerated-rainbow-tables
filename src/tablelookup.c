#include "tablelookup.h"

void lookup(FILE* rainbow_file){
    long rainbow_size;
    char* rainbow_table;

    rainbow_size = get_file_size(rainbow_file);
    rainbow_table = malloc(sizeof(char) * (rainbow_size + 1));
    rainbow_table[rainbow_size] = '\0';


}

void extract_reduced_vals(char* complete_table, char* extracted_table){
    char* token;
    char* token_saved;
    unsigned long counter = 3; // which token we're processing

    // Initial setup
    strtok_r(complete_table, LOOKUP_DELIMS, &token_saved);
    token = strtok_r(NULL, LOOKUP_DELIMS, &token_saved);
    safer_strncpy(extracted_table, token, strlen(token) + 1);
    strcat(extracted_table, NEWLINE_STRING);

    token = strtok_r(NULL, LOOKUP_DELIMS, &token_saved);
    while (token != NULL){
        if (counter % 2 == 0){
            strcat(extracted_table, token);
            strcat(extracted_table, NEWLINE_STRING);
        }
        token = strtok_r(NULL, LOOKUP_DELIMS, &token_saved);
        counter++;
    }
}
