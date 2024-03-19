#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f4xx_hal.h>
#include "console.h"

void HAL_MspInit(void); // Use on HAL_Init() function

void SysTick_Handler(void);

static inline TickType_t delay_ms_to_ticks(uint32_t delay);
static void taskPrintf(void *params);

int main(void) {
    HAL_Init();

    console_init();

    (void)xTaskCreate(taskPrintf, "check", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();

    return 0;
}

void HAL_MspInit(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
}

void SysTick_Handler(void) {
    HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1)
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
#endif /* INCLUDE_xTaskGetSchedulerState */
        xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
    }
#endif /* INCLUDE_xTaskGetSchedulerState */
}

static inline TickType_t delay_ms_to_ticks(uint32_t delay) {
    return (delay / (uint32_t)portTICK_PERIOD_MS);
}

static void taskPrintf(void *params) {
    (void)params;

    for( ;; ) {
        console_send("Hello world\r\n");
        vTaskDelay(delay_ms_to_ticks(500u));
    }
}
