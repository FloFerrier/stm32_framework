set(BUILD_TARGET "${SELECTED_BOARD}_${CMAKE_BUILD_TYPE}" CACHE INTERNAL "")

add_executable(${BUILD_TARGET}
    Src/stm32f4xx_it.c
    Src/system_stm32f4xx.c
    Src/main_f4.c
    Startup/startup_stm32f446retx.s
    Src/syscalls.c
    Src/sysmem.c
)

target_include_directories(${BUILD_TARGET} PRIVATE
    Inc
    ${CMAKE_SOURCE_DIR}/HAL/Inc
    ${CMAKE_SOURCE_DIR}/HAL/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/HAL/STM32F4xx_HAL_Driver/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/CMSIS/include
    ${CMAKE_SOURCE_DIR}/CMSIS/Device/ST/STM32F4xx/Include
)

target_compile_definitions(${BUILD_TARGET} PRIVATE
    -DSTM32F446xx
    -DUSE_HAL_DRIVER
    -D${SELECTED_BOARD}
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}/"
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(${BUILD_TARGET} PRIVATE STM32F4_HAL)

target_compile_options(${BUILD_TARGET} PRIVATE
    -mcpu=${CPU}
    -mthumb
    -mfpu=${FPU}
    -mfloat-abi=${FLOAT_ABI}
    -fdata-sections
    -ffunction-sections
    -Wall
    -Wextra
    $<$<CONFIG:Debug>:-Og -g -gdwarf-2>
    $<$<CONFIG:Release>:-O2>
)

target_link_options(${BUILD_TARGET} PRIVATE
    -T${LINKER_FILE}
    -mcpu=${CPU}
    -mthumb
    -mfpu=${FPU}
    -mfloat-abi=${FLOAT_ABI}
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=output.map,--cref
    -Wl,--print-memory-usage
    -Wl,--gc-sections
)