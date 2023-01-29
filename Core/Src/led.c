#include "led.h"
#include "log.h"
#include "log.h"

static void USER_LED_Init(void);

void USER_LED_Init(void)
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(USER_LED_PORT, USER_LED_PIN, GPIO_PIN_RESET);

    /*Configure GPIO pin : LD2_Pin */
    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin = USER_LED_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW,
    };
    HAL_GPIO_Init(USER_LED_PORT, &GPIO_InitStruct);
}

void USER_LED_Task(void *pvParams)
{
  (void) pvParams;

    USER_LED_Init();
    static uint32_t counter = 0;

    while(1)
    {
        USER_LOG_Debug("Led blinking %d", ++counter);
        HAL_GPIO_TogglePin(USER_LED_PORT, USER_LED_PIN);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}