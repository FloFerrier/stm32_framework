set(BUILD_TARGET firmware)

add_executable(${BUILD_TARGET})

target_sources(${BUILD_TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sysmem.c
)

target_link_libraries(${BUILD_TARGET} PRIVATE
    stm32_hal_driver
    #freertos_kernel
)

target_compile_options(${BUILD_TARGET} PRIVATE
    -mcpu=${CPU}
    -mfpu=${FPU}
    -mfloat-abi=${FLOAT_ABI}
    -Wall
    -Wextra
)

target_link_options(${BUILD_TARGET} PRIVATE
    -T${LINKER_FILE}
    -mcpu=${CPU}
    -mfpu=${FPU}
    -mfloat-abi=${FLOAT_ABI}
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=output.map,--cref
    -Wl,--print-memory-usage
    -Wl,--gc-sections
)

message("OPENOCD_TARGET_BOARD=${OPENOCD_TARGET_BOARD}")

find_program(OPENOCD_Executable Name openocd REQUIRED)

add_custom_target(flash
    COMMAND ${OPENOCD_Executable} -f ${CMAKE_SOURCE_DIR}/config/openocd.cfg -c "setup ${OPENOCD_TARGET_BOARD}" -c "program_release ${CMAKE_CURRENT_BINARY_DIR}/${BUILD_TARGET}.elf"
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${BUILD_TARGET}.elf
)

add_custom_target(debug
    COMMAND ${OPENOCD_Executable} -f ${CMAKE_SOURCE_DIR}/config/openocd.cfg -c "setup ${OPENOCD_TARGET_BOARD}"
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${BUILD_TARGET}.elf
)
