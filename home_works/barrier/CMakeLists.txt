cmake_minimum_required (VERSION 2.8)
project (barrier)
include_directories(../thread_pool ../thread_pool/thread_safe_queue)
add_executable(barrier test.cc)
set_property(TARGET barrier PROPERTY CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
include(CTest)
add_test(barrier barrier)
