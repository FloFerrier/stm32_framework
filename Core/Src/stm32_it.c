#include "main.h"
#include "stm32_it.h"
#include "FreeRTOS.h"
#include "task.h"

void NMI_Handler(void)
{
  while (1)
  {
    // Nothing
  }
}

void HardFault_Handler(void)
{
  while (1)
  {
    // Nothing
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
    // Ntohing
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
    // Nothing
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
    // Nothing
  }
}

void DebugMon_Handler(void)
{
  // Nothing
}

void SysTick_Handler(void)
{
HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
}