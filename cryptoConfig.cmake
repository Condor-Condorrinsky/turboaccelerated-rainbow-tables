add_library(crypto STATIC IMPORTED)
find_library(CRYPTO_LIBRARY_PATH crypto)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION "${CRYPTO_LIBRARY_PATH}")
