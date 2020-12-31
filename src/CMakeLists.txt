
find_package( Threads REQUIRED)

add_library( thread_pool
    STATIC
        thread_pool.cpp
)

target_include_directories( thread_pool
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    # PRIVATE
    #     ${CMAKE_SOURCE_DIR}/src/include
)

target_link_directories( thread_pool
    PUBLIC
        Threads::Threads
)