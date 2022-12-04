include(ExternalProject)

ExternalProject_Add(STM32F4xx_HAL_Driver
  GIT_REPOSITORY "https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git"
  GIT_TAG "v1.8.1"
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/HAL/STM32F4xx_HAL_Driver"
  BINARY_DIR ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)