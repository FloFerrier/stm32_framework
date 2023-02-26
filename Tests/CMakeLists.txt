enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake)

set(PREFIX "test_")

setup_target_for_coverage_lcov(
  NAME coverage
  EXECUTABLE ctest
  EXCLUDE ${CMAKE_SOURCE_DIR}/Tests/*
)

macro(add_unit_test testname)
    add_executable(${PREFIX}${ARGV0}
    # Add here if you have shared ".c"
    ${ARGN})

    target_include_directories(${PREFIX}${ARGV0} PRIVATE
        ${CMAKE_SOURCE_DIR}/Core/Log
        ${CMAKE_SOURCE_DIR}/Core/Log/Driver
        ${CMAKE_SOURCE_DIR}/Tests/mock
    )

    target_compile_features(${PREFIX}${ARGV0} PRIVATE c_std_99)
    target_compile_definitions(${PREFIX}${ARGV0} PRIVATE -DUTEST -DDEBUG)
    target_compile_options(${PREFIX}${ARGV0} PRIVATE -O0 -g3 -Wall -W -Wextra -c --coverage)

    target_link_libraries(${PREFIX}${ARGV0} PRIVATE cmocka-static m)
    target_link_options(${PREFIX}${ARGV0} PRIVATE --coverage)

    add_test(NAME ${PREFIX}${ARGV0} COMMAND $<TARGET_FILE:${PREFIX}${ARGV0}>)
    append_coverage_compiler_flags_to_target(${PREFIX}${ARGV0})
endmacro()

add_unit_test(log_driver
    ${CMAKE_SOURCE_DIR}/Tests/log_driver/main.c
    ${CMAKE_SOURCE_DIR}/Core/Log/Driver/log_driver.c
)

add_unit_test(log_app
    ${CMAKE_SOURCE_DIR}/Tests/log/main.c
    ${CMAKE_SOURCE_DIR}/Core/Log/log.c
    ${CMAKE_SOURCE_DIR}/Tests/mock/mock_freertos.c
    ${CMAKE_SOURCE_DIR}/Tests/mock/mock_stm32l1xx.c
    ${CMAKE_SOURCE_DIR}/Tests/mock/mock_log_driver.c
)