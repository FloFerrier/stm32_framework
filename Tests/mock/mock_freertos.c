#include "mock_freertos.h"

void mock_assert_call_xTaskGetTickCount(TickType_t ret) {
    expect_function_call(xTaskGetTickCount);
    will_return(xTaskGetTickCount, ret);
}

TickType_t xTaskGetTickCount(void) {
    function_called();
    return mock();
}

void mock_assert_call_xTaskDelayUntil(TickType_t pxPreviousWakeTime,
                                      TickType_t xTimeIncrement,
                                      BaseType_t ret) {
    expect_function_call(xTaskDelayUntil);
    expect_value(xTaskDelayUntil, xTimeIncrement, xTimeIncrement);
    will_return(xTaskDelayUntil, pxPreviousWakeTime);
    will_return(xTaskDelayUntil, ret);
}

BaseType_t xTaskDelayUntil(TickType_t *const pxPreviousWakeTime,
                           const TickType_t xTimeIncrement) {
    function_called();
    check_expected(xTimeIncrement);
    *pxPreviousWakeTime = mock();
    return mock();
}

void mock_assert_call_xTaskCreateStatic(TaskFunction_t pxTaskCode,
                                        const char *const pcName,
                                        const uint32_t ulStackDepth,
                                        void *const pvParameters,
                                        UBaseType_t uxPriority,
                                        TaskHandle_t ret) {
    expect_function_call(xTaskCreateStatic);
    expect_value(xTaskCreateStatic, pxTaskCode, pxTaskCode);
    will_return(xTaskCreateStatic, pcName);
    expect_value(xTaskCreateStatic, ulStackDepth, ulStackDepth);
    expect_value(xTaskCreateStatic, pvParameters, pvParameters);
    expect_value(xTaskCreateStatic, uxPriority, uxPriority);
    will_return(xTaskCreateStatic, ret);
}

TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
                               const char *const pcName,
                               const uint32_t ulStackDepth,
                               void *const pvParameters, UBaseType_t uxPriority,
                               StackType_t *const puxStackBuffer,
                               StaticTask_t *const pxTaskBuffer) {
    function_called();
    assert_non_null(puxStackBuffer);
    assert_non_null(pxTaskBuffer);
    check_expected(pxTaskCode);
    assert_string_equal(mock(), pcName);
    check_expected(ulStackDepth);
    check_expected(pvParameters);
    check_expected(uxPriority);
    return (TaskHandle_t)mock();
}

void mock_assert_call_eTaskGetState(TaskHandle_t xTask, eTaskState ret) {
    expect_function_call(eTaskGetState);
    expect_value(eTaskGetState, xTask, xTask);
    will_return(eTaskGetState, ret);
}

eTaskState eTaskGetState(TaskHandle_t xTask) {
    function_called();
    check_expected(xTask);
    return mock();
}

void mock_assert_call_vTaskSuspend(TaskHandle_t xTaskToSuspend) {
    expect_function_call(vTaskSuspend);
    expect_value(vTaskSuspend, xTaskToSuspend, xTaskToSuspend);
}

void vTaskSuspend(TaskHandle_t xTaskToSuspend) {
    function_called();
    check_expected(xTaskToSuspend);
}

void mock_assert_call_vTaskResume(TaskHandle_t xTaskToResume) {
    expect_function_call(vTaskResume);
    expect_value(vTaskResume, xTaskToResume, xTaskToResume);
}

void vTaskResume(TaskHandle_t xTaskToResume) {
    function_called();
    check_expected(xTaskToResume);
}

void mock_assert_call_vTaskDelete(TaskHandle_t xTaskToDelete) {
    expect_function_call(vTaskDelete);
    expect_value(vTaskDelete, xTaskToDelete, xTaskToDelete);
}

void vTaskDelete(TaskHandle_t xTaskToDelete) {
    function_called();
    check_expected(xTaskToDelete);
}

void mock_assert_call_xSemaphoreCreateMutexStatic(SemaphoreHandle_t ret) {
    expect_function_call(xSemaphoreCreateMutexStatic);
    will_return(xSemaphoreCreateMutexStatic, ret);
}

SemaphoreHandle_t xSemaphoreCreateMutexStatic(
    StaticSemaphore_t *pxMutexBuffer) {
    function_called();
    assert_non_null(pxMutexBuffer);
    return (SemaphoreHandle_t)mock();
}

void mock_assert_call_vSemaphoreDelete(SemaphoreHandle_t xSemaphore) {
    expect_function_call(vSemaphoreDelete);
    expect_value(vSemaphoreDelete, xSemaphore, xSemaphore);
}

void vSemaphoreDelete(SemaphoreHandle_t xSemaphore) {
    function_called();
    check_expected(xSemaphore);
}

void mock_assert_call_xSemaphoreTake(SemaphoreHandle_t xSemaphore,
                                     TickType_t xBlockTime, BaseType_t ret) {
    expect_function_call(xSemaphoreTake);
    expect_value(xSemaphoreTake, xSemaphore, xSemaphore);
    expect_value(xSemaphoreTake, xBlockTime, xBlockTime);
    will_return(xSemaphoreTake, ret);
}

BaseType_t xSemaphoreTake(SemaphoreHandle_t xSemaphore, TickType_t xBlockTime) {
    function_called();
    check_expected(xBlockTime);
    check_expected(xSemaphore);
    return mock();
}

void mock_assert_call_xSemaphoreGive(SemaphoreHandle_t xSemaphore,
                                     BaseType_t ret) {
    expect_function_call(xSemaphoreGive);
    expect_value(xSemaphoreGive, xSemaphore, xSemaphore);
    will_return(xSemaphoreGive, ret);
}

BaseType_t xSemaphoreGive(SemaphoreHandle_t xSemaphore) {
    function_called();
    check_expected(xSemaphore);
    return mock();
}

void mock_assert_call_xQueueCreate(const UBaseType_t uxQueueLength,
                                   const UBaseType_t uxItemSize,
                                   QueueHandle_t ret) {
    expect_function_call(xQueueCreate);
    expect_value(xQueueCreate, uxQueueLength, uxQueueLength);
    expect_value(xQueueCreate, uxItemSize, uxItemSize);
    will_return(xQueueCreate, ret);
}

QueueHandle_t xQueueCreate(const UBaseType_t uxQueueLength,
                           const UBaseType_t uxItemSize) {
    function_called();
    check_expected(uxQueueLength);
    check_expected(uxItemSize);
    return (QueueHandle_t)mock();
}

void mock_assert_call_xQueueSend(QueueHandle_t xQueue,
                                 const void *pvItemToQueue,
                                 uint32_t pvItemToQueueSize,
                                 TickType_t xTicksToWait, BaseType_t ret) {
    expect_function_call(xQueueSend);
    expect_value(xQueueSend, xQueue, xQueue);
    will_return(xQueueSend, pvItemToQueue);
    will_return(xQueueSend, pvItemToQueueSize);
    expect_value(xQueueSend, xTicksToWait, xTicksToWait);
    will_return(xQueueSend, ret);
}

BaseType_t xQueueSend(QueueHandle_t xQueue, const void *const pvItemToQueue,
                      TickType_t xTicksToWait) {
    function_called();
    check_expected(xQueue);
    const void *expected = (const void *)mock();
    uint32_t size = mock();
    assert_memory_equal(expected, pvItemToQueue, size);
    check_expected(xTicksToWait);
    return mock();
}

void mock_assert_call_xQueueReceive(QueueHandle_t xQueue,
                                    const void *const pvBuffer,
                                    uint32_t pvBufferSize,
                                    TickType_t xTicksToWait, BaseType_t ret) {
    expect_function_call(xQueueReceive);
    expect_value(xQueueReceive, xQueue, xQueue);
    will_return(xQueueReceive, pvBuffer);
    will_return(xQueueReceive, pvBufferSize);
    expect_value(xQueueReceive, xTicksToWait, xTicksToWait);
    will_return(xQueueReceive, ret);
}

BaseType_t xQueueReceive(QueueHandle_t xQueue, void *const pvBuffer,
                         TickType_t xTicksToWait) {
    function_called();
    check_expected(xQueue);
    const void *const buffer = mock_ptr_type(void *);
    uint32_t size = mock();
    memcpy(pvBuffer, buffer, size);
    check_expected(xTicksToWait);
    return mock();
}