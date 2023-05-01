cmake_minimum_required(VERSION 3.0)
project(Automata)

set(BIN_DIR ${Automata_SOURCE_DIR}/bin)
set(SRC_DIR ${Automata_SOURCE_DIR}/src)
set(LIB_DIR ${Automata_SOURCE_DIR}/lib)
set(INC_DIR ${Automata_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})

set(CMAKE_BINARY_DIR ${Automata_SOURCE_DIR}/build)

add_library(automata ${SRC_DIR}/automata.c)
add_library(automataIO ${SRC_DIR}/writeAutomata.c ${SRC_DIR}/readAutomata.c)
add_library(utils ${SRC_DIR}/utils/LinkedList.c ${SRC_DIR}/utils/Set.c)
add_executable(main ${SRC_DIR}/main.c)
include_directories(${INC_DIR})
target_include_directories(automata PUBLIC ${INC_DIR})
target_link_libraries(main automata automataIO utils m)