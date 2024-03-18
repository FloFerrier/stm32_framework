set(BUILD_TARGET ${SELECTED_BOARD}_${CMAKE_BUILD_TYPE})

add_executable(${BUILD_TARGET}
    core/main.c
    core/syscalls.c
    core/sysmem.c
)

target_compile_definitions(${BUILD_TARGET} PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}/"
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(${BUILD_TARGET} PRIVATE
    stm32_hal_driver
    freertos_kernel
)

target_compile_options(${BUILD_TARGET} PUBLIC
    -mcpu=${CPU}
    -mthumb
    -mfloat-abi=${FLOAT_ABI}
    -fdata-sections
    -ffunction-sections
    -Wall
    -Wextra
    $<$<CONFIG:Debug>:-Og -g -gdwarf-2>
    $<$<CONFIG:Release>:-O2>
)

target_link_options(${BUILD_TARGET} PUBLIC
    -T${LINKER_FILE}
    -mcpu=${CPU}
    -mthumb
    -mfloat-abi=${FLOAT_ABI}
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=output.map,--cref
    -Wl,--print-memory-usage
    -Wl,--gc-sections
)

message("OPENOCD_TARGET_BOARD=${OPENOCD_TARGET_BOARD}")

add_custom_target(flash
    COMMAND openocd -f config/openocd.cfg -c "setup ${OPENOCD_TARGET_BOARD}" -c "program_release ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SELECTED_BOARD}_${CMAKE_BUILD_TYPE}.elf"
    DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SELECTED_BOARD}_${CMAKE_BUILD_TYPE}.elf
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)