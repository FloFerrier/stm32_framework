#include "main.h"
#include "stm32f4xx_it.h"

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
    // Nothing
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

void SVC_Handler(void)
{
  // Nothing
}

void DebugMon_Handler(void)
{
  // Nothing
}

void PendSV_Handler(void)
{
  // Nothing
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}