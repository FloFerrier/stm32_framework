#ifndef CORE_LOG_H
#define CORE_LOG_H

#include "main.h"
#include "log_driver.h"

typedef enum {
    USER_LOG_SUCCESS = 0,
    USER_LOG_ERROR_DRIVER = 1,
    USER_LOG_ERROR_DMA = 1,
    USER_LOG_ERROR_USART = 2,
    USER_LOG_ERROR_OS = 3,
} user_log_error_e;

user_log_error_e USER_LOG_Init(void);
void USER_LOG_Task(void *pvParams);

#define USER_LOG_Fatal(fmt, ...) LOG_Send(LOG_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Error(fmt, ...) LOG_Send(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Warn(fmt, ...)  LOG_Send(LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Info(fmt, ...)  LOG_Send(LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Trace(fmt, ...) LOG_Send(LOG_TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define USER_LOG_Debug(fmt, ...) LOG_Send(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif /* CORE_LOG_H */