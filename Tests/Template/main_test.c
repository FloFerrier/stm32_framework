#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>

static void template(void **state)
{
    assert_true(true);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(template),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}