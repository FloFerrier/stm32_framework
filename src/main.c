#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f4xx_hal.h>
#include "console.h"

void HAL_MspInit(void); // Use on HAL_Init() function

void SysTick_Handler(void);

static void task_shell(void *params);

int main(void) {
    HAL_Init();

    console_init();
    (void)xTaskCreate(task_shell, "shell", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

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

static void task_shell(void *params) {
    (void)params;

    char character = 0;
    bool isSuccess = true;

    for( ;; ) {
        isSuccess = console_receive(&character);
        if(isSuccess == true) {
            if(character >= 0x20  && character <= 0x7E) {
                console_send("%c", character);
            }
            else {
                switch (character)
                {
                case 0x0D: // CR: '\r'
                case 0x0A: // LF: '\n
                    console_send("\r\n");
                    break;
                default:
                    console_send(" 0%x ", character);
                    break;
                }
            }
        }
    }
}
