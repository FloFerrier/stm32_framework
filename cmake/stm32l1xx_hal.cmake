include(FetchContent)

FetchContent_Declare(
  STM32_HAL_Driver
  GIT_REPOSITORY https://github.com/STMicroelectronics/stm32l1xx_hal_driver.git
  GIT_TAG v1.4.4
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/HAL/STM32_HAL_Driver
)

FetchContent_Declare(
  STM32_CMSIS_Device
  GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_l1.git
  GIT_TAG v2.3.2
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/HAL/CMSIS/Device
)

FetchContent_MakeAvailable(STM32_HAL_Driver)
FetchContent_MakeAvailable(STM32_CMSIS_Device)

set(SPECIFIC_BOARD_HAL "STM32L152xE" CACHE INTERNAL "")
set(STARTUP_FILE "startup_stm32l152xe.s" CACHE INTERNAL "")
set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
set( FREERTOS_PORT "GCC_ARM_CM3" CACHE STRING "" FORCE)
set(CPU "cortex-m3")
set(FLOAT_ABI "soft")
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/config/STM32L152RETx_FLASH.ld)