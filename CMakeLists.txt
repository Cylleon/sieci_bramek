cmake_minimum_required(VERSION 3.0.0)
project(sieci_bramek VERSION 0.1.0)

set(CMAKE_C_STANDARD 90)

include(CTest)
enable_testing()

set(SOURCES src/main.c src/node.c src/node.h src/logic_gates.h src/logic_gates.c src/file_reader.h src/file_reader.c src/logical_circuit.h src/logical_circuit.c src/line_reader.h src/line_reader.c
    src/file_writer.h src/file_writer.c)
add_executable(sieci_bramek ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
