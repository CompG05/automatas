cmake_minimum_required(VERSION 3.0)
project(Automata)

add_library(automata automata.c)
add_executable(main main.c)
target_link_libraries(main automata)
