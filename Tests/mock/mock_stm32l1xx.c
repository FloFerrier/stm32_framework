#include "mock_stm32l1xx.h"

#include <string.h>

GPIO_TypeDef mock_GPIOA = {0};
USART_TypeDef mock_USART2 = {0};
DMA_Stream_TypeDef mock_DMA1_Stream7 = {0};

void mock_assert_call_HAL_UART_Receive(UART_HandleTypeDef *huart,
                                       const uint8_t *pData, uint16_t Size,
                                       uint32_t Timeout,
                                       HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_Receive);
    expect_value(HAL_UART_Receive, huart, huart);
    will_return(HAL_UART_Receive, pData);
    will_return(HAL_UART_Receive, Size);
    expect_value(HAL_UART_Receive, Timeout, Timeout);
    will_return(HAL_UART_Receive, ret);
}

HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData,
                                   uint16_t Size, uint32_t Timeout) {
    const uint8_t *ExptpData = (const uint8_t *)mock();
    uint16_t ExptSize = mock();

    function_called();
    check_expected(huart);
    assert_true(Size >= ExptSize);
    check_expected(Timeout);
    memcpy(pData, ExptpData, ExptSize);
    return mock();
}

void mock_assert_call_HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                        const uint8_t *pData, uint16_t Size,
                                        uint32_t Timeout,
                                        HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_Transmit);
    expect_value(HAL_UART_Transmit, huart, huart);
    expect_string(HAL_UART_Transmit, pData, pData);
    expect_value(HAL_UART_Transmit, Size, Size);
    expect_value(HAL_UART_Transmit, Timeout, Timeout);
    will_return(HAL_UART_Transmit, ret);
}

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                    const uint8_t *pData, uint16_t Size,
                                    uint32_t Timeout) {
    function_called();
    check_expected(huart);
    check_expected(pData);
    check_expected(Size);
    check_expected(Timeout);
    return mock();
}

void mock_assert_call_HAL_UART_Receive_IT(UART_HandleTypeDef *huart,
                                          const uint8_t *pData, uint16_t Size,
                                          HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_Receive_IT);
    expect_value(HAL_UART_Receive_IT, huart, huart);
    expect_value(HAL_UART_Receive_IT, Size, Size);
    expect_value(HAL_UART_Receive_IT, pData, pData);
    will_return(HAL_UART_Receive_IT, ret);
}

HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData,
                                      uint16_t Size) {
    function_called();
    check_expected(huart);
    check_expected(Size);
    check_expected(pData);
    return mock();
}

void mock_assert_call_HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart,
                                            const uint8_t *pData, uint16_t Size,
                                            HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_Transmit_DMA);
    expect_value(HAL_UART_Transmit_DMA, huart, huart);
    expect_string(HAL_UART_Transmit_DMA, pData, pData);
    expect_value(HAL_UART_Transmit_DMA, Size, Size);
    will_return(HAL_UART_Transmit_DMA, ret);
}

HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart,
                                        const uint8_t *pData, uint16_t Size) {
    function_called();
    check_expected(huart);
    check_expected(pData);
    check_expected(Size);
    return mock();
}

void mock_assert_call_HAL_UART_Transmit_IT(UART_HandleTypeDef *huart,
                                           const uint8_t *pData, uint16_t Size,
                                           HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_Transmit_IT);
    expect_value(HAL_UART_Transmit_IT, huart, huart);
    expect_memory(HAL_UART_Transmit_IT, pData, pData, Size);
    expect_value(HAL_UART_Transmit_IT, Size, Size);
    will_return(HAL_UART_Transmit_IT, ret);
}

HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart,
                                       const uint8_t *pData, uint16_t Size) {
    function_called();
    check_expected(huart);
    check_expected(pData);
    check_expected(Size);
    return mock();
}

void mock_assert_call_HAL_UART_RegisterCallback(
    UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
    pUART_CallbackTypeDef pCallback, HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_RegisterCallback);
    expect_value(HAL_UART_RegisterCallback, huart, huart);
    expect_value(HAL_UART_RegisterCallback, CallbackID, CallbackID);
    expect_value(HAL_UART_RegisterCallback, pCallback, pCallback);
    will_return(HAL_UART_RegisterCallback, ret);
}

HAL_StatusTypeDef HAL_UART_RegisterCallback(
    UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
    pUART_CallbackTypeDef pCallback) {
    function_called();
    check_expected(huart);
    check_expected(CallbackID);
    check_expected(pCallback);
    return mock();
}

void mock_assert_call_HAL_GPIO_Init(GPIO_TypeDef *GPIOx,
                                    GPIO_InitTypeDef *GPIO_Init) {
    expect_function_call(HAL_GPIO_Init);
    expect_value(HAL_GPIO_Init, GPIOx, GPIOx);
    expect_memory(HAL_GPIO_Init, GPIO_Init, GPIO_Init, sizeof(*GPIO_Init));
    (void)GPIO_Init;
}

void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init) {
    function_called();
    check_expected(GPIOx);
    check_expected(GPIO_Init);
    (void)GPIO_Init;
}

void mock_assert_call_HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                        GPIO_PinState PinState) {
    expect_function_call(HAL_GPIO_WritePin);
    expect_value(HAL_GPIO_WritePin, GPIOx, GPIOx);
    expect_value(HAL_GPIO_WritePin, GPIO_Pin, GPIO_Pin);
    expect_value(HAL_GPIO_WritePin, PinState, PinState);
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                       GPIO_PinState PinState) {
    function_called();
    check_expected(GPIOx);
    check_expected(GPIO_Pin);
    check_expected(PinState);
}

void mock_assert_call_HAL_DMA_Init(DMA_HandleTypeDef *hdma,
                                   HAL_StatusTypeDef ret) {
    expect_function_call(HAL_DMA_Init);
    expect_value(HAL_DMA_Init, hdma, hdma);
    will_return(HAL_DMA_Init, ret);
}

HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma) {
    function_called();
    check_expected(hdma);
    return mock();
}

void mock_assert_call_HAL_NVIC_SetPriority(IRQn_Type IRQn,
                                           uint32_t PreemptPriority,
                                           uint32_t SubPriority) {
    expect_function_call(HAL_NVIC_SetPriority);
    expect_value(HAL_NVIC_SetPriority, IRQn, IRQn);
    expect_value(HAL_NVIC_SetPriority, PreemptPriority, PreemptPriority);
    expect_value(HAL_NVIC_SetPriority, SubPriority, SubPriority);
}

void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority,
                          uint32_t SubPriority) {
    function_called();
    check_expected(IRQn);
    check_expected(PreemptPriority);
    check_expected(SubPriority);
}

void mock_assert_call_HAL_NVIC_EnableIRQ(IRQn_Type IRQn) {
    expect_function_call(HAL_NVIC_EnableIRQ);
    expect_value(HAL_NVIC_EnableIRQ, IRQn, IRQn);
}

void HAL_NVIC_EnableIRQ(IRQn_Type IRQn) {
    function_called();
    check_expected(IRQn);
}

void mock_assert_call_HAL_UART_Init(UART_HandleTypeDef *huart,
                                    HAL_StatusTypeDef ret) {
    expect_function_call(HAL_UART_Init);
    expect_value(HAL_UART_Init, huart, huart);
    will_return(HAL_UART_Init, ret);
}

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart) {
    function_called();
    check_expected(huart);
    return mock();
}

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart) { (void)huart; }

void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma) { (void)hdma; }