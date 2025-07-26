cmake_minimum_required(VERSION 3.21)
project(Quiet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Point to Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Quiet src/main.cpp)

if (WIN32)
  target_link_options(Quiet PRIVATE "-mwindows")
endif()

target_link_libraries(Quiet PRIVATE Qt6::Widgets)
