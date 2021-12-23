cmake_minimum_required(VERSION 3.20)
project(lab_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(lab_2 main.cpp menu.cpp menu.h prog1.cpp prog1.h)

add_executable(writer lab2/writer.cpp)
add_executable(reader lab2/reader.cpp)
