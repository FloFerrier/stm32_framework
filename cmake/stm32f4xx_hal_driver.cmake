include(FetchContent)

FetchContent_Declare(
  STM32_HAL_Driver
  GIT_REPOSITORY https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
  GIT_TAG v1.8.1
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/HAL/STM32_HAL_Driver
)

FetchContent_MakeAvailable(STM32_HAL_Driver)