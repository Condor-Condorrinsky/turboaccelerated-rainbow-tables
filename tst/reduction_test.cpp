#include <gtest/gtest.h>
extern "C" {
    #include "../src/reduction.h"
}

TEST(ReductionTest, ReduceTest){
    const unsigned char example_digest[MD5_DIGEST_LENGTH] =
            {234, 127, 200, 43, 89, 55, 190, 255,
             20, 167, 203, 39, 75, 150, 183, 110};
    char output_buffer[MD5_DIGEST_LENGTH + 1];
    const char* pattern = "15_10_7_12_3_0_8_1";

    reduce(example_digest, output_buffer, pattern, sizeof output_buffer);

    int result = strcmp(output_buffer, "gvvxraux");
    printf("%s\n", output_buffer);
    EXPECT_TRUE(result == 0) << "Reduction output not equal to expected value";
}
