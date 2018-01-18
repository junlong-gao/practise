cmake_minimum_required(VERSION 2.8)
project(cpp_lab)
enable_testing()
set(CMAKE_CXX_COMPILER "clang++")

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17 -g3 -Wall  -Wextra")

set(driver src/main.cpp)
set(smart_pointers src/sptr.cpp)
set(move src/msem.cpp)
set(concurrency src/concurrency.cpp)

set(template "")
file(GLOB SRCS "include/*.hpp")
foreach(file ${SRCS})
    set(template ${MODULES_HEADERS} ${file})
    message("# template = ${template}")
endforeach()

add_executable(demo ${driver}
                    ${smart_pointers}
                    ${concurrency}
                    ${move}
                    ${template})




