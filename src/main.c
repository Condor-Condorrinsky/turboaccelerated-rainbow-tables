#include <stdio.h>
#include <stddef.h>
#include "tablegen.h"
#include "tablelookup.h"

/* Error codes */
#define ERR_OPEN_INPUT          (-1)
#define ERR_OPEN_OUTPUT         (-2)
#define ERR_CLOSE_INPUT         (-3)
#define ERR_CLOSE_OUTPUT        (-4)

int find_in_table(char* input_file, const char* hash);

int gen_table(char* input_file, char* output_file);

int help();

int main(int argc, char *argv[]){
    int exit_stat = 0;
    char hash_upper[HASH_STRING_MIN_LEN];

    if (argc == 1){
        exit_stat = help();
        return exit_stat;
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0){
            exit_stat = help();
            return exit_stat;
        }
    }

    if (argc == 4 && strcmp(argv[1], "gen-table") == 0){
        exit_stat = gen_table(argv[2], argv[3]);
    }
    if (argc == 4 && strcmp(argv[1], "look-up") == 0){
        str_to_uppercase(argv[3], hash_upper, sizeof hash_upper);
        hash_upper[1] = 'x';
        exit_stat = find_in_table(argv[2], hash_upper);
    }

    printf("Nothing to do\n");
    return exit_stat;
}

int find_in_table(char* input_file, const char* hash){
    printf("Performing look up, please wait...\n");
    FILE* in = fopen(input_file, "r");
    if (in == NULL){
        fprintf(stderr, "Couldn't open input file\n");
        return ERR_OPEN_INPUT;
    }
    lookup(in, hash);
    if (fclose(in)){
        fprintf(stderr, "Couldn't close input file\n");
        return ERR_CLOSE_INPUT;
    }
    return EXIT_SUCCESS;
}

int gen_table(char* input_file, char* output_file){
    printf("Generating table, please wait...\n");
    FILE* in = fopen(input_file, "r");
    FILE* out = fopen(output_file, "wb+");
    if (in == NULL){
        fprintf(stderr, "Couldn't open input file\n");
        return ERR_OPEN_INPUT;
    }
    if (out == NULL){
        fprintf(stderr, "Couldn't open/create output file\n");
        return ERR_OPEN_OUTPUT;
    }
    generate_rainbow_table(in, out);
    if (fclose(in)){
        fprintf(stderr, "Couldn't close input file\n");
        return ERR_CLOSE_INPUT;
    }
    if (fclose(out)){
        fprintf(stderr,
                "Couldn't close output file, table might be malformed; please generate once again\n");
        return ERR_CLOSE_OUTPUT;
    }
    printf("Table generated successfully\n");
    return 0;
}

int help(){
    printf("------------------------------TURBOACCELERATED RAINBOW TABLES------------------------------\n");
    printf("Small program to generate MD5 rainbow tables and perform hash look up on them.\n");
    printf("Usage:\n");
    printf("    ./trb gen-table INPUT_FILE OUTPUT_FILE - generating table from list of passwords\n");
    printf("    ./trb look-up TABLE_FILE HASH          - performing hash look-up on generated table\n");
    printf("Where:\n");
    printf("    INPUT_FILE  - file with passes to generate rainbow table from; newline separated with trailing newline\n");
    printf("    OUTPUT_FILE - file to store generated rainbow table; if not exists, will be created\n");
    printf("    TABLE_FILE  - file with pre-generated rainbow table\n");
    printf("    HASH        - hash to look for in table\n");
    printf("Flags:\n");
    printf("    -h - show this help and exit; overwrites all other flags and options\n");
    return EXIT_SUCCESS;
}
