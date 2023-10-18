#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include "tablegen.h"
#include "tablelookup.h"

/* Error codes */
#define ERR_OPEN_INPUT          (-1)
#define ERR_OPEN_OUTPUT         (-2)
#define ERR_CLOSE_INPUT         (-3)
#define ERR_CLOSE_OUTPUT        (-4)
#define ERR_PARSE_ARGS          (-5)

int launch(int argc, char* argv[]);

void parse_flags(int argc, char *argv[], TableMetadata* meta);

int find_in_table(char* input_file, const char* hash, TableMetadata* meta);

int gen_table(char* input_file, char* output_file, TableMetadata* meta);

int help();

int main(int argc, char *argv[]){
    int exit_stat = launch(argc, argv);

    printf("Nothing to do\n");

    return exit_stat;
}

int launch(int argc, char* argv[]){
    int ret;
    char* input_file;
    char* output_file;
    char* hash_upper;
    TableMetadata table;

    parse_flags(argc, argv, &table);

    input_file = malloc(strlen(argv[optind+1]) * sizeof(char) + 1);
    strcpy(input_file, argv[optind+1]);

    if (strcmp(argv[optind], "gen-table") == 0){
        output_file = malloc(strlen(argv[optind+2]) * sizeof(char) + 1);
        strcpy(input_file, argv[optind+2]);
        ret = gen_table(input_file, output_file, &table);
        free(output_file);
    }
    else if (strcmp(argv[optind], "look-up") == 0){
        hash_upper = malloc(strlen(argv[optind+2]) * sizeof(char) + 1);
        strcpy(hash_upper, argv[optind+2]);
        str_to_uppercase(hash_upper, hash_upper, sizeof hash_upper);
        hash_upper[1] = 'x';
        ret = find_in_table(input_file, hash_upper, &table);
        free(hash_upper);
    }
    else {
        fprintf(stderr, "Unrecognized command, no action will be taken\n");
        ret = ERR_PARSE_ARGS;
        return ret;
    }
    free(input_file);
    return ret;
}

void parse_flags(int argc, char *argv[], TableMetadata* meta){
    int opt;
    int cast_c;
    init_TableMetadata(meta, DEFAULT_CHAIN_LEN, DEFAULT_CHARSET);

    while ((opt = getopt(argc, argv, ":hs:c:")) != -1){
        switch (opt) {
            case 'h': // help
                help();
                exit(EXIT_SUCCESS);
            case 's': // character set
                if (strcmp(optarg, CHARSETS_STR[DIGITS]) == 0){
                    meta->charset = DIGITS;
                } else if (strcmp(optarg, CHARSETS_STR[ALPHANUMERIC]) == 0){
                    meta->charset = ALPHANUMERIC;
                } else if (strcmp(optarg, CHARSETS_STR[ASCII_PRINTABLE]) == 0){
                    meta->charset = ASCII_PRINTABLE;
                } else {
                    fprintf(stderr, "Passed unrecognized charset, aborting\n");
                    exit(ERR_PARSE_ARGS);
                }
                break;
            case 'c': // chain length
                cast_c = (int) strtol(optarg, NULL, 10);
                if (cast_c < 1) {
                    fprintf(stderr, "WARNING: cast of chain length to int failed, aborting\n");
                    exit(ERR_PARSE_ARGS);
                }
                meta->chain_len = cast_c;
                break;
            case ':':
                fprintf(stderr, "Specified an option without specifying a value\n");
                exit(ERR_PARSE_ARGS);
            case '?':
                fprintf(stderr, "Unknown option: %c\n", optopt);
                break;
            default:
                fprintf(stderr, "Parsing flags failed\n");
                exit(ERR_PARSE_ARGS);
        }
    }
}

int find_in_table(char* input_file, const char* hash, TableMetadata* meta){
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

int gen_table(char* input_file, char* output_file, TableMetadata* meta){
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
    generate_rainbow_table(in, out, meta);
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
    return EXIT_SUCCESS;
}

int help(){
    printf("------------------------------TURBOACCELERATED RAINBOW TABLES------------------------------\n");
    printf("Small program to generate MD5 rainbow tables and perform hash look up on them.\n");
    printf("Usage:\n");
    printf("    ./trb gen-table [-sc] INPUT_FILE OUTPUT_FILE - generating table from list of passwords\n");
    printf("    ./trb look-up TABLE_FILE HASH                - performing hash look-up on generated table\n");
    printf("Where:\n");
    printf("    INPUT_FILE  - file with passes to generate rainbow table from; newline separated with trailing newline\n");
    printf("    OUTPUT_FILE - file to store generated rainbow table; if not exists, will be created\n");
    printf("    TABLE_FILE  - file with pre-generated rainbow table\n");
    printf("    HASH        - hash to look for in table\n");
    printf("Flags:\n");
    printf("    -h - show this help and exit\n");
    printf("    -s - set character set used in generation; allowed values: DIGITS, ALPHANUMERIC, ASCII_PRINTABLE\n");
    printf("    -c - set chain length; a positive integer\n");
    return EXIT_SUCCESS;
}
