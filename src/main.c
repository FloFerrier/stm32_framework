#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f4xx_hal.h>

#define UART_BUFFER_LEN_MAX (255u)

static char uartBuffer[UART_BUFFER_LEN_MAX+1] = "";
static UART_HandleTypeDef uartHandle = {0};

void HAL_MspInit(void); // Use on HAL_Init() function

void SysTick_Handler(void);

static inline TickType_t delay_ms_to_ticks(uint32_t delay);
static void uart_init(void);
static void uart_send(const char* format, ...);
static void taskPrintf(void *params);

int main(void) {
    HAL_Init();

    uart_init();

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

/* UART2
 * Tx -> PA2
 * Rx -> PA3
 */
static void uart_init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();

    GPIO_InitTypeDef gpioInit = {
        .Pin = GPIO_PIN_2 | GPIO_PIN_3,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
        .Alternate = GPIO_AF7_USART2,
    };
    (void)HAL_GPIO_Init(GPIOA, &gpioInit);

    uartHandle.Instance = USART2;
    uartHandle.Init.BaudRate = 115200;
    uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    uartHandle.Init.StopBits = UART_STOPBITS_1;
    uartHandle.Init.Parity = UART_PARITY_NONE;
    uartHandle.Init.Mode = UART_MODE_TX_RX;
    uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    (void)HAL_UART_Init(&uartHandle);
}

static void uart_send(const char* format, ...) {
    va_list va;
    va_start(va, format);
    uint16_t uartBufferLen = 0;
    uartBufferLen = (uint16_t)vsnprintf(uartBuffer, UART_BUFFER_LEN_MAX, format, va);
    va_end(va);
    (void)HAL_UART_Transmit(&uartHandle, (uint8_t*)uartBuffer, uartBufferLen, (uint32_t)1000u);
}

static void taskPrintf(void *params) {
    (void)params;

    for( ;; ) {
        uart_send("Hello world\r\n");
        vTaskDelay(delay_ms_to_ticks(500u));
    }
}
