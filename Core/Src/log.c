#include "log.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define USER_LOG_LEN_MAX (255U)

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

QueueHandle_t queueUserLog;

static log_level_e _level = LOG_INFO;

void DMA1_Channel7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart2_tx);
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2);
}

void USER_UART_Init(void)
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
        Error_Handler();
    }
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
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
        Error_Handler();
   }
    __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);
    __HAL_RCC_DMA1_CLK_ENABLE();
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

    queueUserLog = xQueueCreate(1, sizeof(char) * (USER_LOG_LEN_MAX+1));
    if(NULL == queueUserLog)
    {
        Error_Handler();
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

void USER_LOG_SetLevel(log_level_e level)
{
    switch (level)
    {
    case LOG_FATAL :
    case LOG_ERROR :
    case LOG_WARN :
    case LOG_INFO :
    case LOG_TRACE :
    case LOG_DEBUG :
        _level = level;
        break;
    default:
        break;
    }
}

log_level_e USER_LOG_GetLevel(void)
{
    return _level;
}

void USER_LOG_Send(log_level_e level, const char *file, int line, const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    char buffer[USER_LOG_LEN_MAX+1] = "";
    char *ptr = buffer;

    if(_level < level)
    {
        return;
    }

    switch (level)
    {
    case LOG_FATAL :
        ptr += sprintf(ptr, "[FATAL] ");
        break;
    case LOG_ERROR :
        ptr += sprintf(ptr, "[ERROR] ");
        break;
    case LOG_WARN :
        ptr += sprintf(ptr, "[WARN] ");
        break;
    case LOG_INFO :
        ptr += sprintf(ptr, "[INFO] ");
        break;
    case LOG_TRACE :
        ptr += sprintf(ptr, "[TRACE] ");
        break;
    case LOG_DEBUG :
        ptr += sprintf(ptr, "[DEBUG] ");
    default:
        break;
    }

    if(LOG_DEBUG == level)
    {
        ptr += sprintf(ptr, "(%s:%d) ", file, line);
    }
    ptr += vsprintf(ptr, fmt, args);
    va_end(args);
    ptr += sprintf(ptr, "\r\n");
    xQueueSend(queueUserLog, buffer, 100);
}