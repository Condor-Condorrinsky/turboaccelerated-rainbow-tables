add_library(GTest STATIC IMPORTED)
find_library(GTEST_LIBRARY_PATH GTest HINTS /usr/lib64)
set_target_properties(GTest PROPERTIES IMPORTED_LOCATION "${GTEST_LIBRARY_PATH}")
