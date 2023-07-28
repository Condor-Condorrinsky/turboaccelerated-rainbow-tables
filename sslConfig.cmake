add_library(ssl STATIC IMPORTED)
find_library(SSL_LIBRARY_PATH ssl)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION "${SSL_LIBRARY_PATH}")
