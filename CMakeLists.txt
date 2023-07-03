cmake_minimum_required (VERSION 3.0)
project (dummy-dbg)

add_compile_options(-std=c++20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(ext/libelfin ext/linenoise include)
add_executable(dummy-dbg 
    src/main.cpp
    src/debugger.cpp
    ext/linenoise/linenoise.c)

add_custom_target(
   libelfin
   COMMAND make
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ext/libelfin
)
target_link_libraries(dummy-dbg
                      ${PROJECT_SOURCE_DIR}/ext/libelfin/dwarf/libdwarf++.so
                      ${PROJECT_SOURCE_DIR}/ext/libelfin/elf/libelf++.so)
add_dependencies(dummy-dbg libelfin)

