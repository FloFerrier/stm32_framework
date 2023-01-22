#ifndef CORE_LOG_H
#define CORE_LOG_H

#include "main.h"

void USER_LOG_Task(void *pvParams);

void USER_UART_Init(void);
void USER_LOG_Send(const char *format, ...);

#endif /* CORE_LOG_H */