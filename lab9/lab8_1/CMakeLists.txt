cmake_minimum_required(VERSION 3.16)
project(lab8_1 C)

set(CMAKE_C_STANDARD 11)
find_package (Threads REQUIRED)
add_executable(lab8_1 main.c mythreads.h)


target_link_libraries(lab8_1
        ${CMAKE_THREAD_LIBS_INIT}
)