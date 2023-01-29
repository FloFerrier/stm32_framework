#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "log_driver.h"

#define LOG_LEN_MAX (255U)

typedef struct {
    log_level_e level;
    bool color;
    log_fcnt_t send_interface;
} log_t;

extern log_t _log;

extern void LOG_GenerateIndex(log_level_e level, const char *file, int line, char *index, uint32_t *size);
extern void LOG_GenerateEndOfLine(char *endOfLine, uint32_t *len);

static void mock_USER_LOG_SendData(const char *data, const uint32_t len)
{
    check_expected(data);
    check_expected(len);
}

static int setup(void **state)
{
    (void) state;
    log_t *fixture = &_log;
    fixture->level = LOG_INFO;
    fixture->color = true;
    fixture->send_interface = mock_USER_LOG_SendData;
    *state = fixture;
    return 0;
}

static int teardown(void **state)
{
    return 0;
}

static void test_LOG_Init_ptrNull(void **state)
{
    (void) state;
    log_t *fixture = &_log;
    log_interface_t interface = {
        .send_data = NULL,
    };
    LOG_Init(interface);
    assert_int_equal(fixture->level, LOG_DEBUG);
    assert_true(fixture->color);
    assert_ptr_equal(fixture->send_interface, NULL);
    assert_ptr_not_equal(fixture->send_interface, &mock_USER_LOG_SendData);
}

static void test_LOG_Init_normal(void **state)
{
    (void) state;
    log_t *fixture = &_log;
    log_interface_t interface = {
        .send_data = mock_USER_LOG_SendData,
    };
    LOG_Init(interface);
    assert_int_equal(fixture->level, LOG_DEBUG);
    assert_true(fixture->color);
    assert_ptr_not_equal(fixture->send_interface, NULL);
    assert_ptr_equal(fixture->send_interface, &mock_USER_LOG_SendData);
}

static void test_LOG_SetLevel_fatal(void **state)
{
    log_t *fixture = *state;
    LOG_SetLevel(LOG_FATAL);
    assert_int_equal(fixture->level, LOG_FATAL);
}

static void test_LOG_SetLevel_error(void **state)
{
    log_t *fixture = *state;
    LOG_SetLevel(LOG_ERROR);
    assert_int_equal(fixture->level, LOG_ERROR);
}

static void test_LOG_SetLevel_warn(void **state)
{
    log_t *fixture = *state;
    LOG_SetLevel(LOG_WARN);
    assert_int_equal(fixture->level, LOG_WARN);
}

static void test_LOG_SetLevel_info(void **state)
{
    log_t *fixture = *state;
    LOG_SetLevel(LOG_INFO);
    assert_int_equal(fixture->level, LOG_INFO);
}

static void test_LOG_SetLevel_trace(void **state)
{
    log_t *fixture = *state;
    LOG_SetLevel(LOG_TRACE);
    assert_int_equal(fixture->level, LOG_TRACE);
}

static void test_LOG_SetLevel_debug(void **state)
{
    log_t *fixture = *state;
    LOG_SetLevel(LOG_DEBUG);
    assert_int_equal(fixture->level, LOG_DEBUG);
}

static void test_LOG_SetLevel_incorrect(void **state)
{
    log_t *fixture = *state;
    const int level = 0xFF;
    LOG_SetLevel(level);
    assert_int_not_equal(fixture->level, level);
}

static void test_LOG_GetLevel_atStart(void **state)
{
    log_t *fixture = *state;
    assert_int_equal(LOG_INFO, LOG_GetLevel());
}

static void test_LOG_GetLevel_normal(void **state)
{
    log_t *fixture = *state;
    fixture->level = LOG_DEBUG;
    assert_int_equal(LOG_DEBUG, LOG_GetLevel());
}

static void test_LOG_DisableColor(void **state)
{
    log_t *fixture = *state;
    LOG_DisableColor();
    assert_false(fixture->color);
}

static void test_LOG_EnableColor(void **state)
{
    log_t *fixture = *state;
    LOG_EnableColor();
    assert_true(fixture->color);
}

static void test_LOG_GenerateIndex_normal(void **state)
{
    log_t *fixture = *state;
    char *index = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    uint32_t len  = 0;
    LOG_GenerateIndex(LOG_FATAL, (char*) "filename", 100, index, &len);
    assert_string_equal(index, "\x1b[35m[FATAL] ");
    assert_int_equal(len, 13);
    free(index);
}

static void test_LOG_GenerateIndex_debug(void **state)
{
    log_t *fixture = *state;
    char *index = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    uint32_t len  = 0;
    LOG_GenerateIndex(LOG_DEBUG, (char*) "filename.c", 100, index, &len);
    assert_string_equal(index, "\x1b[32m[DEBUG] (filename.c:100) ");
    assert_int_equal(len, 30);
    free(index);
}

static void test_LOG_GenerateIndex_withoutColor(void **state)
{
    log_t *fixture = *state;
    char *index = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    uint32_t len  = 0;
    fixture->color = false;
    LOG_GenerateIndex(LOG_FATAL, (char*) "filename", 100, index, &len);
    assert_string_equal(index, "[FATAL] ");
    assert_int_equal(len, 8);
    free(index);
}

static void test_LOG_GenerateEndOfLine_normal(void **state)
{
    log_t *fixture = *state;
    char *endOfLine = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    uint32_t len  = 0;
    LOG_GenerateEndOfLine(endOfLine, &len);
    assert_string_equal(endOfLine, "\x1b[0m\r\n");
    assert_int_equal(len, 6);
    free(endOfLine);
}

static void test_LOG_GenerateEndOfLine_withoutColor(void **state)
{
    log_t *fixture = *state;
    fixture->color = false;
    char *endOfLine = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    uint32_t len  = 0;
    LOG_GenerateEndOfLine(endOfLine, &len);
    assert_string_equal(endOfLine, "\r\n");
    assert_int_equal(len, 2);
    free(endOfLine);
}

static void test_LOG_Send_normal(void **state)
{
    log_t *fixture = *state;
    char *message = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    int message_len = snprintf(message, LOG_LEN_MAX, "\x1b[35m[FATAL] Text with argument 10\x1b[0m\r\n");
    expect_string(mock_USER_LOG_SendData, data, message);
    expect_value(mock_USER_LOG_SendData, len, message_len);
    LOG_Send(LOG_FATAL, (char*) "filename.c", 100, "Text with argument %d", 10);
    free(message);
}

static void test_LOG_Send_withoutColor(void **state)
{
    log_t *fixture = *state;
    fixture->color = false;
    fixture->level = LOG_DEBUG;
    char *message = calloc(1, sizeof(char) * (LOG_LEN_MAX + 1));
    int message_len = snprintf(message, LOG_LEN_MAX, "[DEBUG] (filename.c:100) Text with argument 10\r\n");
    expect_string(mock_USER_LOG_SendData, data, message);
    expect_value(mock_USER_LOG_SendData, len, message_len);
    LOG_Send(LOG_DEBUG, (char*) "filename.c", 100, "Text with argument %d", 10);
    free(message);
}

static void test_LOG_Send_skip(void **state)
{
    log_t *fixture = *state;
    /* mock_USER_LOG_SendData is not called */
    LOG_Send(LOG_DEBUG, (char*) "filename.c", 100, "Text with argument %d", 10);
}

static void test_integ_LOG_normal(void **state)
{
    /* Initialization step */
    (void) state;
    log_interface_t log_interface = {
        .send_data = mock_USER_LOG_SendData,
    };
    LOG_Init(log_interface);
    assert_int_equal(_log.level, LOG_DEBUG);
    assert_true(_log.color);
    assert_ptr_equal(_log.send_interface, mock_USER_LOG_SendData);

    /* Set Log Level step */
    LOG_SetLevel(LOG_FATAL);
    assert_int_equal(_log.level, LOG_FATAL);

    /* Get Log Level step */
    assert_int_equal(LOG_GetLevel(), LOG_FATAL);

    /* Disable ASCII Color step */
    LOG_DisableColor();
    assert_false(_log.color);

    /* Send Log message (FATAL level)*/
    expect_string(mock_USER_LOG_SendData, data, "[FATAL] Test a message with arg : 10\r\n");
    expect_value(mock_USER_LOG_SendData, len, 0x26);
    LOG_Send(LOG_FATAL, (char*) "filename.c", 100, "Test a message with arg : %d", 10);

    /* Skip Log message due to log level */
    LOG_Send(LOG_DEBUG, (char*) "filename.c", 100, "Test a message %d", 10);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_LOG_Init_ptrNull),
        cmocka_unit_test(test_LOG_Init_normal),

        cmocka_unit_test_setup_teardown(test_LOG_SetLevel_fatal, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_SetLevel_error, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_SetLevel_warn, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_SetLevel_info, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_SetLevel_trace, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_SetLevel_debug, setup, teardown),

        cmocka_unit_test_setup_teardown(test_LOG_GetLevel_atStart, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_GetLevel_normal, setup, teardown),

        cmocka_unit_test_setup_teardown(test_LOG_DisableColor, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_EnableColor, setup, teardown),

        cmocka_unit_test_setup_teardown(test_LOG_GenerateIndex_normal, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_GenerateIndex_debug, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_GenerateIndex_withoutColor, setup, teardown),

        cmocka_unit_test_setup_teardown(test_LOG_GenerateEndOfLine_normal, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_GenerateEndOfLine_withoutColor, setup, teardown),

        cmocka_unit_test_setup_teardown(test_LOG_Send_normal, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_Send_withoutColor, setup, teardown),
        cmocka_unit_test_setup_teardown(test_LOG_Send_skip, setup, teardown),

        cmocka_unit_test(test_integ_LOG_normal),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}