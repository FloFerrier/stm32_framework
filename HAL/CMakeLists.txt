if(SELECTED_BOARD STREQUAL stm32f446re)
    include(${CMAKE_SOURCE_DIR}/cmake/stm32f4xx_hal.cmake)
    set(SPECIFIC_BOARD_HAL "STM32F446xx" CACHE INTERNAL "")
    set(STARTUP_FILE ".s" CACHE INTERNAL "")
elseif(SELECTED_BOARD STREQUAL stm32l152re)
    include(${CMAKE_SOURCE_DIR}/cmake/stm32l1xx_hal.cmake)
    set(SPECIFIC_BOARD_HAL "STM32L152xE" CACHE INTERNAL "")
    set(STARTUP_FILE "startup_stm32l152xe.s" CACHE INTERNAL "")
else()
	message(FATAL_ERROR " STM32 HAL Driver is not supported ...")
endif()

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