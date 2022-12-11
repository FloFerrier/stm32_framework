include(FetchContent)

FetchContent_Declare(
    freertos_kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG V10.5.1
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/OS/FreeRTOS
)

FetchContent_MakeAvailable(freertos_kernel)