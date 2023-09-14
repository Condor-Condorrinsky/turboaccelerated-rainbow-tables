add_library(cmocka STATIC IMPORTED)
find_library(CMOCKA_LIBRARY_PATH cmocka)
set_target_properties(cmocka PROPERTIES IMPORTED_LOCATION "${CMOCKA_LIBRARY_PATH}")
