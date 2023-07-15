cmake_minimum_required(VERSION 3.14)

project(SimpleTimeTracker LANGUAGES CXX)

file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
include_directories(include/)

find_package(SQLite3 REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARIES})