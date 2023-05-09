cmake_minimum_required(VERSION 3.0)
project(Automata)

set(BIN_DIR ${Automata_SOURCE_DIR}/bin)
set(SRC_DIR ${Automata_SOURCE_DIR}/src)
set(LIB_DIR ${Automata_SOURCE_DIR}/lib)
set(INC_DIR ${Automata_SOURCE_DIR}/include)
set(TEST_DIR ${Automata_SOURCE_DIR}/test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})

set(CMAKE_BINARY_DIR ${Automata_SOURCE_DIR}/build)

list(APPEND LIBS automata automataIO utils)

include_directories(${INC_DIR})

add_library(automata ${SRC_DIR}/automata.c)
target_link_libraries(automata m)

add_library(automataIO ${SRC_DIR}/writeAutomata.c ${SRC_DIR}/readAutomata.c)
target_link_libraries(automataIO automata)
add_library(utils ${SRC_DIR}/utils/LinkedList.c ${SRC_DIR}/utils/Set.c)

add_executable(runAutomata ${SRC_DIR}/runAutomata.c)
target_link_libraries(runAutomata ${LIBS})

add_executable(toAFD ${SRC_DIR}/toAFD.c)
target_link_libraries(toAFD ${LIBS})

add_executable(testAFNtoAFD ${TEST_DIR}/testAFNtoAFD.c)
target_link_libraries(testAFNtoAFD ${LIBS})

add_executable(testRunAutomata ${TEST_DIR}/testRunAutomata.c)
target_link_libraries(testRunAutomata ${LIBS})

add_executable(testReadAutomata ${TEST_DIR}/testReadAutomata.c)
target_link_libraries(testReadAutomata ${LIBS})

add_executable(testWriteAutomata ${TEST_DIR}/testWriteAutomata.c)
target_link_libraries(testWriteAutomata ${LIBS})

add_executable(testIntegrity1 ${TEST_DIR}/testIntegrity1.c)
target_link_libraries(testIntegrity1 ${LIBS})

add_executable(testIntegrity2 ${TEST_DIR}/testIntegrity2.c)
target_link_libraries(testIntegrity2 ${LIBS})

add_executable(testIntegrity3 ${TEST_DIR}/testIntegrity3.c)
target_link_libraries(testIntegrity3 ${LIBS})