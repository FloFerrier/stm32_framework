#include "mock_log_driver.h"

void mock_assert_call_LOG_Init(log_interface_s interface) {
    expect_function_call(LOG_Init);
    expect_value(LOG_Init, interface.send_data, interface.send_data);
}

void LOG_Init(log_interface_s interface) {
    function_called();
    check_expected(interface.send_data);
}

void mock_assert_call_LOG_SetLevel(log_level_e level) {
    expect_function_call(LOG_SetLevel);
    expect_value(LOG_SetLevel, level, level);
}

void LOG_SetLevel(log_level_e level) {
    function_called();
    check_expected(level);
}

void mock_assert_call_LOG_GetLevel(log_level_e ret) {
    expect_function_call(LOG_GetLevel);
    will_return(LOG_GetLevel, ret);
}

log_level_e LOG_GetLevel(void) {
    function_called();
    return mock();
}

void mock_assert_call_LOG_DisableColor(void) {
    expect_function_call(LOG_DisableColor);
}

void LOG_DisableColor(void) { function_called(); }

void mock_assert_call_LOG_EnableColor(void) {
    expect_function_call(LOG_EnableColor);
}

void LOG_EnableColor(void) { function_called(); }

void mock_assert_call_LOG_Send(log_level_e level, const char *file, int line,
                               const char *fmt, ...) {
    expect_function_call(LOG_Send);
    expect_value(LOG_Send, level, level);
}

void LOG_Send(log_level_e level, const char *file, int line, const char *fmt,
              ...) {
    function_called();
    check_expected(level);
}