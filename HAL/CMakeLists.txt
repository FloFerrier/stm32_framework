file(GLOB STM32_HAL_SRC_FILES CONFIGURE_DEPENDS
    STM32_HAL_Driver/Src/*.c
    CMSIS/Device/Source/Templates/*.c
    CMSIS/Device/Source/Templates/gcc/${STARTUP_FILE}
)

add_library(stm32_hal_driver STATIC ${STM32_HAL_SRC_FILES})

target_include_directories(stm32_hal_driver PUBLIC
    Inc
    STM32_HAL_Driver/Inc
    STM32_HAL_Driver/Inc/Legacy
    CMSIS/Device/Include
    CMSIS/Include
)

target_compile_definitions(stm32_hal_driver PUBLIC
    -D${SPECIFIC_BOARD_HAL}
)