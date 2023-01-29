set(TARGET "Log_driver")

set(TEST_TARGET "${CMAKE_BUILD_TYPE}_${TARGET}" CACHE INTERNAL "")

add_executable(${TEST_TARGET}
    main_test.c
    ${CMAKE_SOURCE_DIR}/Core/Log/Driver/log_driver.c
)

target_include_directories(${TEST_TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/Core/Log/Driver
)

target_compile_definitions(${TEST_TARGET} PRIVATE
    -DUTEST
    -DDEBUG
    #-DUSE_HAL_DRIVER
    #-DSTM32F446xx
    #-DUSE_FULL_ASSERT
)

target_link_libraries(${TEST_TARGET} PRIVATE cmocka-static)

target_compile_options(${TEST_TARGET} PRIVATE --coverage)

target_link_options(${TEST_TARGET} PRIVATE
    --coverage
    #-Wl,--wrap=
)

enable_testing()
add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})