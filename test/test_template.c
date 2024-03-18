#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

static void test_empty() {
    fail_msg("Need to implement it ...");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_empty),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}