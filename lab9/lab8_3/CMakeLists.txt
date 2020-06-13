cmake_minimum_required(VERSION 3.16)
project(lab8_3 C)

set(CMAKE_C_STANDARD 11)
find_package (Threads REQUIRED)
add_executable(lab8_3 main.c mythreads.h)


target_link_libraries(lab8_3
        ${CMAKE_THREAD_LIBS_INIT}
        )