#ifndef TEST_MOCK_STM32F4XX_H
#define TEST_MOCK_STM32F4XX_H

#include <setjmp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "cmocka.h"

/* Dummy values */
#define GPIO_PIN_2 0x0
#define GPIO_PIN_3 0x0
#define GPIO_MODE_AF_PP 0x0
#define GPIO_MODE_OUTPUT_PP 0x0
#define GPIO_NOPULL 0x0
#define GPIO_SPEED_FREQ_LOW 0x0
#define GPIO_SPEED_FREQ_VERY_HIGH 0x0
#define GPIO_AF7_USART2 0x0
#define DMA1_Channel7 0x0
#define DMA_MEMORY_TO_PERIPH 0x0
#define DMA_PINC_DISABLE 0x0
#define DMA_MINC_ENABLE 0x0
#define DMA_PDATAALIGN_BYTE 0x0
#define DMA_MDATAALIGN_BYTE 0x0
#define DMA_NORMAL 0x0
#define DMA_PRIORITY_LOW 0x0
#define DMA_FIFOMODE_DISABLE 0x0
#define UART_WORDLENGTH_8B 0x0
#define UART_STOPBITS_1 0x0
#define UART_MODE_TX_RX 0x0
#define UART_PARITY_NONE 0x0
#define UART_MODE_TX 0x0
#define UART_HWCONTROL_NONE 0x0
#define UART_OVERSAMPLING_16 0x0

#define __HAL_RCC_GPIOA_CLK_ENABLE() (void)0;
#define __HAL_RCC_USART2_CLK_ENABLE() (void)0;
#define __HAL_RCC_DMA1_CLK_ENABLE() (void)0;

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__) (void)0;

typedef enum
{
/******  Cortex-M3 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                        */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt                 */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                         */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                       */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                          */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                    */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                      */

/******  STM32L specific Interrupt Numbers ***********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                               */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt               */
  TAMPER_STAMP_IRQn           = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line   */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup Timer through EXTI Line Interrupt            */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                  */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                    */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                    */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                    */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                    */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                    */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                    */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                         */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                         */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                         */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                         */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                         */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                         */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                         */
  ADC1_IRQn                   = 18,     /*!< ADC1 global Interrupt                                   */
  USB_HP_IRQn                 = 19,     /*!< USB High Priority Interrupt                             */
  USB_LP_IRQn                 = 20,     /*!< USB Low Priority Interrupt                              */
  DAC_IRQn                    = 21,     /*!< DAC Interrupt                                           */
  COMP_IRQn                   = 22,     /*!< Comparator through EXTI Line Interrupt                  */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                           */
  TIM9_IRQn                   = 25,     /*!< TIM9 global Interrupt                                   */
  TIM10_IRQn                  = 26,     /*!< TIM10 global Interrupt                                  */
  TIM11_IRQn                  = 27,     /*!< TIM11 global Interrupt                                  */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                   */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                   */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                   */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                    */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                    */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                    */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                    */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                   */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                   */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                 */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                 */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                 */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                         */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm through EXTI Line Interrupt                   */
  USB_FS_WKUP_IRQn            = 42,     /*!< USB FS WakeUp from suspend through EXTI Line Interrupt  */
  TIM6_IRQn                   = 43,     /*!< TIM6 global Interrupt                                   */
  TIM7_IRQn                   = 44,     /*!< TIM7 global Interrupt                                   */
  TIM5_IRQn                   = 46,     /*!< TIM5 global Interrupt                                   */
  SPI3_IRQn                   = 47,     /*!< SPI3 global Interrupt                                   */
  UART4_IRQn                  = 48,     /*!< UART4 global Interrupt                                  */
  UART5_IRQn                  = 49,     /*!< UART5 global Interrupt                                  */
  DMA2_Channel1_IRQn          = 50,     /*!< DMA2 Channel 1 global Interrupt                         */
  DMA2_Channel2_IRQn          = 51,     /*!< DMA2 Channel 2 global Interrupt                         */
  DMA2_Channel3_IRQn          = 52,     /*!< DMA2 Channel 3 global Interrupt                         */
  DMA2_Channel4_IRQn          = 53,     /*!< DMA2 Channel 4 global Interrupt                         */
  DMA2_Channel5_IRQn          = 54,     /*!< DMA2 Channel 5 global Interrupt                         */
  COMP_ACQ_IRQn               = 56      /*!< Comparator Channel Acquisition global Interrupt         */
} IRQn_Type;

typedef struct {
    uint32_t dummy;
} GPIO_TypeDef;

typedef struct {
    uint32_t dummy;
} DMA_Stream_TypeDef;

typedef struct {
    uint32_t dummy;
} USART_TypeDef;

typedef struct {
    uint32_t BaudRate;
    uint32_t WordLength;
    uint32_t StopBits;
    uint32_t Parity;
    uint32_t Mode;
    uint32_t HwFlowCtl;
    uint32_t OverSampling;
} UART_InitTypeDef;

typedef struct __UART_HandleTypeDef {
    USART_TypeDef *Instance;
    UART_InitTypeDef Init;
} UART_HandleTypeDef;

typedef struct {
    uint32_t Channel;
    uint32_t Direction;
    uint32_t PeriphInc;
    uint32_t MemInc;
    uint32_t PeriphDataAlignment;
    uint32_t MemDataAlignment;
    uint32_t Mode;
    uint32_t Priority;
    uint32_t FIFOMode;
    uint32_t FIFOThreshold;
    uint32_t MemBurst;
    uint32_t PeriphBurst;
} DMA_InitTypeDef;

typedef struct __DMA_HandleTypeDef {
    DMA_Stream_TypeDef *Instance;
    DMA_InitTypeDef Init;
} DMA_HandleTypeDef;

typedef struct {
    uint32_t Pin;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
    uint32_t Alternate;
} GPIO_InitTypeDef;

typedef enum { GPIO_PIN_RESET = 0, GPIO_PIN_SET } GPIO_PinState;

typedef enum {
    HAL_OK = 0x00U,
    HAL_ERROR = 0x01U,
    HAL_BUSY = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef enum {
    HAL_UART_TX_HALFCOMPLETE_CB_ID =
        0x00U, /*!< UART Tx Half Complete Callback ID        */
    HAL_UART_TX_COMPLETE_CB_ID = 0x01U, /*!< UART Tx Complete Callback ID */
    HAL_UART_RX_HALFCOMPLETE_CB_ID =
        0x02U, /*!< UART Rx Half Complete Callback ID        */
    HAL_UART_RX_COMPLETE_CB_ID = 0x03U, /*!< UART Rx Complete Callback ID */
    HAL_UART_ERROR_CB_ID = 0x04U,       /*!< UART Error Callback ID       */
    HAL_UART_ABORT_COMPLETE_CB_ID =
        0x05U, /*!< UART Abort Complete Callback ID          */
    HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID =
        0x06U, /*!< UART Abort Transmit Complete Callback ID */
    HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID =
        0x07U, /*!< UART Abort Receive Complete Callback ID  */
    HAL_UART_WAKEUP_CB_ID = 0x08U, /*!< UART Wakeup Callback ID */

    HAL_UART_MSPINIT_CB_ID = 0x0BU,  /*!< UART MspInit callback ID  */
    HAL_UART_MSPDEINIT_CB_ID = 0x0CU /*!< UART MspDeInit callback ID */

} HAL_UART_CallbackIDTypeDef;

extern GPIO_TypeDef mock_GPIOA;
#define GPIOA &mock_GPIOA
extern USART_TypeDef mock_USART2;
#define USART2 &mock_USART2
extern DMA_Stream_TypeDef mock_DMA1_Stream7;
#define DMA1_Stream3 &mock_DMA1_Stream7

typedef void (*pUART_CallbackTypeDef)(
    UART_HandleTypeDef *huart); /*!< pointer to an UART callback function */

void mock_assert_call_HAL_UART_Receive(UART_HandleTypeDef *huart,
                                       const uint8_t *pData, uint16_t Size,
                                       uint32_t Timeout, HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData,
                                   uint16_t Size, uint32_t Timeout);

void mock_assert_call_HAL_UART_Receive_IT(UART_HandleTypeDef *huart,
                                          const uint8_t *pData, uint16_t Size,
                                          HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData,
                                      uint16_t Size);

void mock_assert_call_HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                        const uint8_t *pData, uint16_t Size,
                                        uint32_t Timeout,
                                        HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                    const uint8_t *pData, uint16_t Size,
                                    uint32_t Timeout);

void mock_assert_call_HAL_UART_Transmit_IT(UART_HandleTypeDef *huart,
                                           const uint8_t *pData, uint16_t Size,
                                           HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart,
                                       const uint8_t *pData, uint16_t Size);

void mock_assert_call_HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart,
                                            const uint8_t *pData, uint16_t Size,
                                            HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart,
                                        const uint8_t *pData, uint16_t Size);

void mock_assert_call_HAL_UART_RegisterCallback(
    UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
    pUART_CallbackTypeDef pCallback, HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_RegisterCallback(
    UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
    pUART_CallbackTypeDef pCallback);

void mock_assert_call_HAL_GPIO_Init(GPIO_TypeDef *GPIOx,
                                    GPIO_InitTypeDef *GPIO_Init);
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);

void mock_assert_call_HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                        GPIO_PinState PinState);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                       GPIO_PinState PinState);

void mock_assert_call_HAL_DMA_Init(DMA_HandleTypeDef *hdma,
                                   HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);

void mock_assert_call_HAL_NVIC_SetPriority(IRQn_Type IRQn,
                                           uint32_t PreemptPriority,
                                           uint32_t SubPriority);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority,
                          uint32_t SubPriority);

void mock_assert_call_HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);

void mock_assert_call_HAL_UART_Init(UART_HandleTypeDef *huart,
                                    HAL_StatusTypeDef ret);
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);

#endif  // TEST_MOCK_STM32F4XX_H
