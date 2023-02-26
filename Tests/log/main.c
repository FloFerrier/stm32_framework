// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>
// clang-format on

#include "log.h"

#define LOG_LEN_MAX (255U)

extern void USART2_IRQHandler(void);
extern void DMA1_Channel7_IRQHandler(void);

void ut(void **state) {
    (void)state;
    assert_true(true);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(ut),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}