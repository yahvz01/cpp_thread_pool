
find_package(GTest REQUIRED)


if(GTEST_FOUND)
    message( STATUS "GTest found")
endif()


include(CTest)

set(THREAD_POOL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include" )
set(THREAD_POOL_SOURCE "${CMAKE_SOURCE_DIR}/src/thread_pool.cpp" )

set(TEST01 ThreadPoolRunning)

message( GTEST_INCLUDE_DIR ${GTEST_INCLUDE_DIRS})
set( GTEST_LIBRARIES "/usr/lib/libgtest.a")
set( GTEST_MAIN_LIBRARIES "/usr/lib/libgtest_main.a")
message( GTEST_LIBRARIES ${GTEST_LIBRARIES})
message( TEST01 ${TEST01})

add_executable( ${TEST01}
    Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/${TEST01}.cpp 
    #${THREAD_POOL_SOURCE}
    )

target_include_directories( ${TEST01} 
    PUBLIC
        #${THREAD_POOL_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIRS}
        )

target_link_directories( ${TEST01}
    PUBLIC
        GTest::GTest
        #GTest::Main        
        #pthread
)

enable_testing()
