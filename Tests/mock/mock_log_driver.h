#ifndef TEST_MOCK_LOG_DRIVER_H
#define TEST_MOCK_LOG_DRIVER_H

#include <setjmp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "cmocka.h"

typedef enum {
    LOG_FATAL = 0,
    LOG_ERROR = 1,
    LOG_WARN = 2,
    LOG_INFO = 3,
    LOG_TRACE = 4,
    LOG_DEBUG = 5,
} log_level_e;

typedef void (*log_fcnt_t)(const char *data, const uint32_t len);

typedef struct {
    log_fcnt_t send_data;
} log_interface_s;

void mock_assert_call_LOG_Init(log_interface_s interface);
void LOG_Init(log_interface_s interface);

void mock_assert_call_LOG_SetLevel(log_level_e level);
void LOG_SetLevel(log_level_e level);

void mock_assert_call_LOG_GetLevel(log_level_e ret);
log_level_e LOG_GetLevel(void);

void mock_assert_call_LOG_DisableColor(void);
void LOG_DisableColor(void);

void mock_assert_call_LOG_EnableColor(void);
void LOG_EnableColor(void);

void mock_assert_call_LOG_Send(log_level_e level, const char *file, int line, const char *fmt, ...);
void LOG_Send(log_level_e level, const char *file, int line, const char *fmt, ...);

#endif /* TEST_MOCK_LOG_DRIVER_H */