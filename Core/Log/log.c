#include "log.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define USER_LOG_LEN_MAX (255U)

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

QueueHandle_t queueUserLog;

void USART2_IRQHandler(void);
void DMA1_Channel7_IRQHandler(void);

void USER_LOG_SendData(const char *data, const uint32_t len);

void DMA1_Channel7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart2_tx);
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2);
}

user_log_error_e USER_LOG_Init(void)
{
    /* GPIO Initialization */
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
    */
    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin = GPIO_PIN_2 | GPIO_PIN_3,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
        .Alternate = GPIO_AF7_USART2,
    };
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* UART Initialization */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if(HAL_OK != HAL_UART_Init(&huart2))
    {
        return USER_LOG_ERROR_USART;
    }
    HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    /* DMA Initialization */
    hdma_usart2_tx.Instance = DMA1_Channel7;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    if(HAL_OK != HAL_DMA_Init(&hdma_usart2_tx))
    {
        return USER_LOG_ERROR_DMA;
   }
    __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);
    __HAL_RCC_DMA1_CLK_ENABLE();
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

    /* FreeRTOS Queue Creation */
    queueUserLog = xQueueCreate(1, sizeof(char) * (USER_LOG_LEN_MAX+1));
    if(NULL == queueUserLog)
    {
        return USER_LOG_ERROR_OS;
    }

    /* Log Driver Initialization */
    log_interface_t log_interface = {
        .send_data = USER_LOG_SendData,
    };
    LOG_Init(log_interface);
    /* Must return USER_LOG_ERROR_DRIVER if fail */

    return USER_LOG_SUCCESS;
}

void USER_LOG_SendData(const char *data, const uint32_t len)
{
    (void) len;
    if((NULL != queueUserLog) && (NULL != data))
    {
        BaseType_t error = xQueueSend(queueUserLog, data, 100);
        if(pdPASS != error)
        {
            // TODO : treat error here
        }
    }
}

void USER_LOG_Task(void *pvParams)
{
    (void) pvParams;

    char buffer[USER_LOG_LEN_MAX+1] = "";
    size_t sizeBuffer = 0;

    while(1)
    {
        xQueueReceive(queueUserLog, (char*)buffer, portMAX_DELAY);
        sizeBuffer = strlen(buffer);
        if(HAL_OK != HAL_UART_Transmit(&huart2, (uint8_t*)buffer, (uint16_t)sizeBuffer, 1000))
        {
            // Nothing
        }
    }
}