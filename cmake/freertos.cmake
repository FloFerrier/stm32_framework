include(FetchContent)

FetchContent_Declare(
    freertos_kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG V10.6.1
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/rtos/freertos_kernel
)

FetchContent_MakeAvailable(freertos_kernel)