cmake_minimum_required(VERSION 3.22)
project(circularBuffer_test)
find_package(GTest REQUIRED)
message(${GTEST_BOTH_LIBRARIES})

enable_testing()
add_executable(${PROJECT_NAME} circularBuffer_test.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest GTest::gtest_main GTest::gmock)
gtest_discover_tests(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/)

# Enable coverage
set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

# Add coverage target
add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
    test -e report && rm -rf mkdir || mkdir report && cd report && gcovr -r "${CMAKE_SOURCE_DIR}/" --html --html-details -o coverage.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating coverage report"
    VERBATIM
)
