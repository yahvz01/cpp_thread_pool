cmake_minimum_required(VERSION 3.15)

project("thread_pool")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/bin")

add_library( thread_pool
    STATIC

)

target_include_directories( thread_pool
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
)