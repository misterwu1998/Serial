cmake_minimum_required(VERSION 3.0.0)
project(testSerial VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCE_CPP ./src/*.cpp)
file(GLOB_RECURSE SOURCE_C ./src/*.c)

include_directories(./include/)

# add_library(Serial SHARED ${SOURCE_CPP} ${SOURCE_C})

add_executable(testSerial main.cpp test_anotherIncluder.cpp)
# target_link_libraries(testSerial Serial)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
