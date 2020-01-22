#include "unity.h"

#ifdef UNIT_TEST

//Sample s;

void test_test(void) {
    TEST_ASSERT_EQUAL(32, 32);
}

void test_test02(void) {
    TEST_ASSERT_EQUAL(31, 31);
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_test);
    RUN_TEST(test_test02);
    UNITY_END();
    return 0;
}

#endif