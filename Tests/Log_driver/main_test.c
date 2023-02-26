#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_driver.h"

#define LOG_LEN_MAX (255U)

typedef struct {
    log_level_e level;
    bool color;
    bool isInitialized;
    log_fcnt_t send_interface;
} log_instance_s;

typedef struct {
    log_instance_s *log_instance;
} fixture_s;

extern void LOG_GenerateIndex(log_level_e level, const char *file, int line,
                              char *index, uint32_t *size);
extern void LOG_GenerateEndOfLine(char *endOfLine, uint32_t *len);

static void mock_USER_LOG_SendData(const char *data, const uint32_t len) {
    check_expected(data);
    check_expected(len);
}

static int setup(void **state) {
    (void)state;
    extern log_instance_s log_instance;
    log_instance.level = LOG_DEBUG;
    log_instance.color = true;
    log_instance.isInitialized = false;
    log_instance.send_interface = mock_USER_LOG_SendData;
    fixture_s *fixture = calloc(1, sizeof(fixture_s));
    fixture->log_instance = &log_instance;
    *state = fixture;
    return 0;
}

static int teardown(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    free(fixture);
    return 0;
}

static void ut_LOG_Init_interfacePtrNull(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    log_interface_s log_interface = {
        .send_data = NULL,
    };
    LOG_Init(log_interface);
    assert_false(fixture->log_instance->isInitialized);
}

static void ut_LOG_Init_nominal(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    log_interface_s log_interface = {
        .send_data = mock_USER_LOG_SendData,
    };
    LOG_Init(log_interface);
    assert_int_equal(fixture->log_instance->level, LOG_DEBUG);
    assert_true(fixture->log_instance->color);
    assert_ptr_not_equal(fixture->log_instance->send_interface, NULL);
    assert_ptr_equal(fixture->log_instance->send_interface,
                     &mock_USER_LOG_SendData);
}

static void ut_LOG_SetLevel_incorrect(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    const int level = 0xFF;
    LOG_SetLevel(level);
    assert_int_not_equal(fixture->log_instance->level, level);
}

static void ut_LOG_SetLevel_nominal(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    int testData[] = {
        LOG_FATAL, LOG_ERROR, LOG_WARN, LOG_INFO, LOG_TRACE, LOG_DEBUG,
    };
    int sizeData = sizeof(testData) / sizeof(*testData);

    for (int i = 0; i < sizeData; i++) {
        print_message("Test parametric [%d/%d]\r\n", i + 1, sizeData);
        LOG_SetLevel(testData[i]);
        assert_int_equal(fixture->log_instance->level, testData[i]);
    }
}

static void ut_LOG_GetLevel_nominal(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    int testData[] = {
        LOG_FATAL, LOG_ERROR, LOG_WARN, LOG_INFO, LOG_TRACE, LOG_DEBUG,
    };
    int sizeData = sizeof(testData) / sizeof(*testData);

    for (int i = 0; i < sizeData; i++) {
        print_message("Test parametric [%d/%d]\r\n", i + 1, sizeData);
        fixture->log_instance->level = testData[i];
        assert_int_equal(LOG_GetLevel(), testData[i]);
    }
}

static void ut_LOG_DisableColor_nominal(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    fixture->log_instance->color = true;
    LOG_DisableColor();
    assert_false(fixture->log_instance->color);
}

static void ut_LOG_EnableColor_nominal(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    fixture->log_instance->color = false;
    LOG_EnableColor();
    assert_true(fixture->log_instance->color);
}

static void ut_LOG_Send_skip(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    fixture->log_instance->isInitialized = true;
    fixture->log_instance->level = LOG_FATAL;
    LOG_Send(LOG_DEBUG, (char *)"filename.c", 100, "Text with argument %d", 10);
}

static void ut_LOG_Send_nominal(void **state) {
    fixture_s *fixture = (fixture_s *)*state;
    fixture->log_instance->isInitialized = true;
    typedef struct {
        log_level_e level;
        bool color;
        char *file;
        int line;
        char *expected_message;
    } test_s;
    test_s testData[] = {
        {
            .level = LOG_FATAL,
            .color = true,
            .file = "testfile.c",
            .line = 100,
            .expected_message = "\x1b[35m[FATAL] Try to send message with "
                                "parameter : 10\x1b[0m\r\n",
        },
        {
            .level = LOG_ERROR,
            .color = true,
            .file = "testfile.c",
            .line = 100,
            .expected_message = "\x1b[31m[ERROR] Try to send message with "
                                "parameter : 10\x1b[0m\r\n",
        },
        {
            .level = LOG_WARN,
            .color = true,
            .file = "testfile.c",
            .line = 100,
            .expected_message = "\x1b[33m[WARN] Try to send message with "
                                "parameter : 10\x1b[0m\r\n",
        },
        {
            .level = LOG_INFO,
            .color = true,
            .file = "testfile.c",
            .line = 100,
            .expected_message = "\x1b[36m[INFO] Try to send message with "
                                "parameter : 10\x1b[0m\r\n",
        },
        {
            .level = LOG_TRACE,
            .color = true,
            .file = "testfile.c",
            .line = 100,
            .expected_message = "\x1b[34m[TRACE] Try to send message with "
                                "parameter : 10\x1b[0m\r\n",
        },
        {
            .level = LOG_DEBUG,
            .color = true,
            .file = "testfile.c",
            .line = 100,
            .expected_message = "\x1b[32m[DEBUG] (testfile.c:100) Try to send "
                                "message with parameter : 10\x1b[0m\r\n",
        },
    };
    int sizeData = sizeof(testData) / sizeof(*testData);
    for (int i = 0; i < sizeData; i++) {
        fixture->log_instance->color = testData[i].color;
        print_message("Test parametric [%d/%d]\r\n", i + 1, sizeData);
        expect_string(mock_USER_LOG_SendData, data,
                      testData[i].expected_message);
        expect_value(mock_USER_LOG_SendData, len,
                     strlen(testData[i].expected_message));
        LOG_Send(testData[i].level, (char *)testData[i].file, testData[i].line,
                 "Try to send message with parameter : %d", 10);
    }
}

static void integ_LOG_nominal(void **state) {
    (void)state;

    extern log_instance_s log_instance;

    /* Initialization step */
    log_interface_s log_interface = {
        .send_data = mock_USER_LOG_SendData,
    };
    LOG_Init(log_interface);
    assert_int_equal(log_instance.level, LOG_DEBUG);
    assert_true(log_instance.color);
    assert_ptr_equal(log_instance.send_interface, mock_USER_LOG_SendData);

    /* Set Log Level step */
    LOG_SetLevel(LOG_FATAL);
    assert_int_equal(log_instance.level, LOG_FATAL);

    /* Get Log Level step */
    assert_int_equal(LOG_GetLevel(), LOG_FATAL);

    /* Disable ASCII Color step */
    LOG_DisableColor();
    assert_false(log_instance.color);

    /* Send Log message (FATAL level)*/
    expect_string(mock_USER_LOG_SendData, data,
                  "[FATAL] Test a message with arg : 10\r\n");
    expect_value(mock_USER_LOG_SendData, len, 0x26);
    LOG_Send(LOG_FATAL, (char *)"filename.c", 100,
             "Test a message with arg : %d", 10);

    /* Skip Log message due to log level */
    LOG_Send(LOG_DEBUG, (char *)"filename.c", 100, "Test a message %d", 10);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(ut_LOG_Init_interfacePtrNull, setup,
                                        teardown),
        cmocka_unit_test_setup_teardown(ut_LOG_Init_nominal, setup, teardown),

        cmocka_unit_test_setup_teardown(ut_LOG_SetLevel_incorrect, setup,
                                        teardown),
        cmocka_unit_test_setup_teardown(ut_LOG_SetLevel_nominal, setup,
                                        teardown),

        cmocka_unit_test_setup_teardown(ut_LOG_GetLevel_nominal, setup,
                                        teardown),

        cmocka_unit_test_setup_teardown(ut_LOG_DisableColor_nominal, setup,
                                        teardown),

        cmocka_unit_test_setup_teardown(ut_LOG_EnableColor_nominal, setup,
                                        teardown),

        cmocka_unit_test_setup_teardown(ut_LOG_Send_skip, setup, teardown),
        cmocka_unit_test_setup_teardown(ut_LOG_Send_nominal, setup, teardown),

        cmocka_unit_test(integ_LOG_nominal),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}