if(SELECTED_BOARD STREQUAL stm32f446re)
    include(${CMAKE_SOURCE_DIR}/cmake/stm32f4xx_hal_driver.cmake)
    set(CMSIS_HAL_INC_FOLDER "CMSIS/Device/ST/STM32F4xx/Include" CACHE INTERNAL "")
    set(SPECIFIC_BOARD_HAL "STM32F446xx" CACHE INTERNAL "")
elseif(SELECTED_BOARD STREQUAL stm32l152re)
    include(${CMAKE_SOURCE_DIR}/cmake/stm32l1xx_hal_driver.cmake)
    set(CMSIS_HAL_INC_FOLDER "CMSIS/Device/ST/STM32L1xx/Include" CACHE INTERNAL "")
    set(SPECIFIC_BOARD_HAL "STM32L152xE" CACHE INTERNAL "")
else()
	message(FATAL_ERROR " STM32 HAL Driver is not supported ...")
endif()

file(GLOB STM32_HAL_SRC_FILES CONFIGURE_DEPENDS STM32_HAL_Driver/Src/*.c)

add_library(stm32_hal_driver STATIC ${STM32_HAL_SRC_FILES})

target_include_directories(stm32_hal_driver PUBLIC
    Inc
    STM32_HAL_Driver/Inc
    STM32_HAL_Driver/Inc/Legacy
    ${CMSIS_HAL_INC_FOLDER}
    CMSIS/Include
)

target_compile_definitions(stm32_hal_driver PUBLIC
    -D${SPECIFIC_BOARD_HAL}
)