#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "fileio_test.c"
#include "md5calc_test.c"
#include "reduction_test.c"
#include "tablegen_test.c"
#include "tablelookup_test.c"

int main(void) {
    const struct CMUnitTest tests[] = {
            // fileio_test.c
            cmocka_unit_test_setup_teardown(load_file_test, fileio_setup, fileio_teardown),
            cmocka_unit_test_setup_teardown(get_file_size_test, fileio_setup, fileio_teardown),
            cmocka_unit_test_setup_teardown(count_lines_test, fileio_setup, fileio_teardown),
            // md5calc_test.c
            cmocka_unit_test(compute_md5_test),
            cmocka_unit_test(convert_md5_to_string_test),
            cmocka_unit_test(convert_string_to_md5_test),
            // reduction_test.c
            cmocka_unit_test(R_test),
            cmocka_unit_test(pad_str_leading_zeroes_test),
            cmocka_unit_test(safer_strncpy_test),
            cmocka_unit_test(unsigned_char_to_ascii_test),
            cmocka_unit_test(unsigned_char_to_small_letter_test),
            // tablegen_test.c
            cmocka_unit_test_setup_teardown(generate_rainbow_table_test, tablegen_setup, tablegen_teardown),
            cmocka_unit_test_setup_teardown(generate_chain_test, tablegen_setup, tablegen_teardown),
            // tablelookup_test.c
            cmocka_unit_test_setup_teardown(lookup_test, tablelookup_setup, tablelookup_teardown),
            cmocka_unit_test_setup_teardown(extract_hashed_vals_test, tablelookup_setup, tablelookup_teardown),
            cmocka_unit_test_setup_teardown(line_to_PassHashChain_test, tablelookup_setup, tablelookup_teardown),
            cmocka_unit_test_setup_teardown(find_hash_test, tablelookup_setup, tablelookup_teardown),
            cmocka_unit_test_setup_teardown(find_hash_in_chain_test, tablelookup_setup, tablelookup_teardown),
            cmocka_unit_test_setup_teardown(str_to_uppercase_test, tablelookup_setup, tablelookup_teardown),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
