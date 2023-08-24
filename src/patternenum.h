#ifndef TURBOACCELERATED_RAINBOW_TABLES_PATTERNENUM_H
#define TURBOACCELERATED_RAINBOW_TABLES_PATTERNENUM_H

const static unsigned int REDUCTION_PATTERNS_SIZE = 8;

enum REDUCTION_PATTERNS{
    REDUCTION_PATTERN0  =  0,
    REDUCTION_PATTERN1  =  1,
    REDUCTION_PATTERN2  =  2,
    REDUCTION_PATTERN3  =  3,
    REDUCTION_PATTERN4  =  4,
    REDUCTION_PATTERN5  =  5,
    REDUCTION_PATTERN6  =  6,
    REDUCTION_PATTERN7  =  7
};

const static char* const REDUCTION_PATTERN_VALUES[] = {
        [REDUCTION_PATTERN0]  = "5_7_10_15_13_1_2_3",
        [REDUCTION_PATTERN1]  = "10_8_0_3_4_7_2_5",
        [REDUCTION_PATTERN2]  = "11_15_13_1_0_6_5_3",
        [REDUCTION_PATTERN3]  = "15_0_1_3_8_12_4_5",
        [REDUCTION_PATTERN4]  = "0_1_2_3_4_5_6_7",
        [REDUCTION_PATTERN5]  = "7_6_5_4_3_2_1_0",
        [REDUCTION_PATTERN6]  = "0_2_4_6_8_10_12_14",
        [REDUCTION_PATTERN7]  = "1_3_5_7_9_11_13_15",
};

#endif //TURBOACCELERATED_RAINBOW_TABLES_PATTERNENUM_H