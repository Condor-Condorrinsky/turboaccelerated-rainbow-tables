add_library(gmp STATIC IMPORTED)
find_library(GMP_LIBRARY_PATH gmp)
set_target_properties(gmp PROPERTIES IMPORTED_LOCATION "${GMP_LIBRARY_PATH}")
