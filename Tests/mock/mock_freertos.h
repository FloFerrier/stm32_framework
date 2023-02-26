#ifndef TEST_MOCK_FREERTOS_H
#define TEST_MOCK_FREERTOS_H

#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cmocka.h"

typedef uint32_t TickType_t;
typedef int32_t BaseType_t;
typedef uint32_t StackType_t;
typedef uint32_t UBaseType_t;

#define configASSERT(x) assert_true(x)
#define configTICK_RATE_HZ ((TickType_t)8000)

#define portMAX_DELAY ((TickType_t)0xffffffffUL)

#define pdFALSE ((BaseType_t)0)
#define pdTRUE ((BaseType_t)1)
#define pdPASS (pdTRUE)
#define pdFAIL (pdFALSE)
#define errQUEUE_EMPTY ((BaseType_t)0)
#define errQUEUE_FULL ((BaseType_t)0)

#define tskIDLE_PRIORITY ((UBaseType_t)0U)

typedef enum {
    eRunning = 0,
    eReady,
    eBlocked,
    eSuspended,
    eDeleted,
    eInvalid
} eTaskState;

typedef struct {
    uint32_t dummy;
} StaticTask_t;

typedef struct tskTaskControlBlock {
    uint32_t dummy;
} tskTCB;
typedef struct tskTaskControlBlock *TaskHandle_t;
typedef void (*TaskFunction_t)(void *);

typedef struct {
    uint32_t dummy;
} StaticSemaphore_t;
struct QueueDefinition {
    uint32_t dummy;
};
typedef struct QueueDefinition *SemaphoreHandle_t;
typedef struct QueueDefinition *QueueHandle_t;

void mock_assert_call_xTaskGetTickCount(TickType_t ret);
TickType_t xTaskGetTickCount(void);

BaseType_t xTaskDelayUntil(TickType_t *const pxPreviousWakeTime,
                           const TickType_t xTimeIncrement);
void mock_assert_call_xTaskDelayUntil(TickType_t pxPreviousWakeTime,
                                      TickType_t xTimeIncrement,
                                      BaseType_t ret);

TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
                               const char *const pcName,
                               const uint32_t ulStackDepth,
                               void *const pvParameters, UBaseType_t uxPriority,
                               StackType_t *const puxStackBuffer,
                               StaticTask_t *const pxTaskBuffer);

void mock_assert_call_xTaskCreateStatic(TaskFunction_t pxTaskCode,
                                        const char *const pcName,
                                        const uint32_t ulStackDepth,
                                        void *const pvParameters,
                                        UBaseType_t uxPriority,
                                        TaskHandle_t ret);

void mock_assert_call_eTaskGetState(TaskHandle_t xTask, eTaskState ret);
eTaskState eTaskGetState(TaskHandle_t xTask);

void mock_assert_call_vTaskSuspend(TaskHandle_t xTaskToSuspend);
void vTaskSuspend(TaskHandle_t xTaskToSuspend);

void mock_assert_call_vTaskResume(TaskHandle_t xTaskToResume);
void vTaskResume(TaskHandle_t xTaskToResume);

void mock_assert_call_vTaskDelete(TaskHandle_t xTaskToDelete);
void vTaskDelete(TaskHandle_t xTaskToDelete);

void mock_assert_call_xSemaphoreCreateMutexStatic(SemaphoreHandle_t ret);
SemaphoreHandle_t xSemaphoreCreateMutexStatic(StaticSemaphore_t *pxMutexBuffer);

void mock_assert_call_vSemaphoreDelete(SemaphoreHandle_t xSemaphore);
void vSemaphoreDelete(SemaphoreHandle_t xSemaphore);

void mock_assert_call_xSemaphoreTake(SemaphoreHandle_t xSemaphore,
                                     TickType_t xBlockTime, BaseType_t ret);
BaseType_t xSemaphoreTake(SemaphoreHandle_t xSemaphore, TickType_t xBlockTime);

void mock_assert_call_xSemaphoreGive(SemaphoreHandle_t xSemaphore,
                                     BaseType_t ret);
BaseType_t xSemaphoreGive(SemaphoreHandle_t xSemaphore);

void mock_assert_call_xQueueCreate(const UBaseType_t uxQueueLength,
                                   const UBaseType_t uxItemSize,
                                   QueueHandle_t ret);
QueueHandle_t xQueueCreate(const UBaseType_t uxQueueLength,
                           const UBaseType_t uxItemSize);

void mock_assert_call_xQueueSend(QueueHandle_t xQueue,
                                 const void *pvItemToQueue,
                                 uint32_t pvItemToQueueSize,
                                 TickType_t xTicksToWait, BaseType_t ret);
BaseType_t xQueueSend(QueueHandle_t xQueue, const void *const pvItemToQueue,
                      TickType_t xTicksToWait);

void mock_assert_call_xQueueReceive(QueueHandle_t xQueue,
                                    const void *const pvBuffer,
                                    uint32_t pvBufferSize,
                                    TickType_t xTicksToWait, BaseType_t ret);
BaseType_t xQueueReceive(QueueHandle_t xQueue, void *const pvBuffer,
                         TickType_t xTicksToWait);

#endif  // TEST_MOCK_FREERTOS_H