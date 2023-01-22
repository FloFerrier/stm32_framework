#ifndef CORE_LED_H
#define CORE_LED_H

#include "main.h"

#define USER_LED_PIN GPIO_PIN_5
#define USER_LED_PORT GPIOA

void USER_LED_Task(void *pvParams);

#endif /* CORE_LED_H */