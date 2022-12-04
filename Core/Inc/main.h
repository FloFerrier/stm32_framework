#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F446xx
#include "stm32f4xx_hal.h"
#endif

#ifdef STM32L152xE
#include "stm32l1xx_hal.h"
#endif

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
