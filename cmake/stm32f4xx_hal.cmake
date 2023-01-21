include(FetchContent)

FetchContent_Declare(
  STM32_HAL_Driver
  GIT_REPOSITORY https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
  GIT_TAG v1.8.1
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/HAL/STM32_HAL_Driver
)

FetchContent_Declare(
  STM32_CMSIS_Device
  GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_f4.git
  GIT_TAG v2.6.8
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/HAL/CMSIS/Device
)

FetchContent_MakeAvailable(STM32_HAL_Driver)
FetchContent_MakeAvailable(STM32_CMSIS_Device)

set(SPECIFIC_BOARD_HAL "STM32F446xx" CACHE INTERNAL "")
set(STARTUP_FILE "startup_stm32f446retx.s" CACHE INTERNAL "")
set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
set( FREERTOS_PORT "GCC_ARM_CM4" CACHE STRING "" FORCE)
set(CPU "cortex-m4")
set(FPU "fpv4-sp-d16")
set(FLOAT_ABI "hard")
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/config/STM32F446RETX_FLASH.ld)