if(SELECTED_BOARD STREQUAL stm32f446re)
    include(${CMAKE_SOURCE_DIR}/cmake/stm32f4xx_hal_driver.cmake)

    file(GLOB STM32F4_SRC_FILES CONFIGURE_DEPENDS STM32F4xx_HAL_Driver/Src/*.c)

    add_library(STM32F4_HAL STATIC ${STM32F4_SRC_FILES})

    target_include_directories(STM32F4_HAL PUBLIC
        Inc
        STM32F4xx_HAL_Driver/Inc
        STM32F4xx_HAL_Driver/Inc/Legacy
        CMSIS/Device/ST/STM32F4xx/Include
        CMSIS/Include
    )

    target_compile_definitions(STM32F4_HAL PUBLIC
        -DSTM32F446xx
    )

else()
	message(FATAL_ERROR " STM32 HAL Driver is not supported ...")
endif()