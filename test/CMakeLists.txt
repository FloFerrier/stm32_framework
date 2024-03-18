enable_testing()

setup_target_for_coverage_lcov(
    NAME coverage
    EXECUTABLE ctest
    EXCLUDE ${CMAKE_SOURCE_DIR}/test/*
)

macro(add_unit_test unitestname)
    add_executable(${ARGV0} ${ARGN})
    target_compile_definitions(${ARGV0} PRIVATE -DUTEST)
    target_compile_options(${ARGV0} PRIVATE --coverage)
    target_link_libraries(${ARGV0} PRIVATE cmocka-static)
    target_link_options(${ARGV0} PRIVATE --coverage)
    add_test(NAME ${ARGV0} COMMAND $<TARGET_FILE:${ARGV0}>)
    append_coverage_compiler_flags_to_target(${ARGV0})
endmacro()

add_unit_test(test_template
    test_template.c
)
