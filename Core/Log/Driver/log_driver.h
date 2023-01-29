#ifndef LOG_DRIVER_H
#define LOG_DRIVER_H

#include <stdint.h>

#ifndef UTEST
#define LOG_STATIC static
#else
#define LOG_STATIC
#endif

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
} log_interface_t;

void LOG_Init(log_interface_t interface);

void LOG_SetLevel(log_level_e level);
log_level_e LOG_GetLevel(void);

void LOG_DisableColor(void);
void LOG_EnableColor(void);

void LOG_Send(log_level_e level, const char *file, int line, const char *fmt, ...);

#endif /* LOG_DRIVER_H */