#ifndef CORE_LOG_H
#define CORE_LOG_H

#include "main.h"

typedef enum {
    LOG_FATAL = 0,
    LOG_ERROR = 1,
    LOG_WARN = 2,
    LOG_INFO = 3,
    LOG_TRACE = 4,
    LOG_DEBUG = 5,
} log_level_e;

void USER_LOG_Task(void *pvParams);

void USER_UART_Init(void);

void USER_LOG_SetLevel(log_level_e level);
log_level_e USER_LOG_GetLevel(void);
void USER_LOG_Send(log_level_e level, const char *file, int line, const char *fmt, ...);

#define USER_LOG_Fatal(fmt, ...) USER_LOG_Send(LOG_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Error(fmt, ...) USER_LOG_Send(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Warn(fmt, ...)  USER_LOG_Send(LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Info(fmt, ...)  USER_LOG_Send(LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Trace(fmt, ...) USER_LOG_Send(LOG_TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Debug(fmt, ...) USER_LOG_Send(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif /* CORE_LOG_H */