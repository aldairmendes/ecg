cmake_minimum_required(VERSION 3.14)
project(ClassificadorECG)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.10
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)

include_directories(include)

add_executable(programa_ecg
    src/main.cpp
    src/ClassificadorECG.cpp
    src/EcgBuffer.cpp
    src/SerialPort.cpp
)

if(MSVC)
    target_compile_options(programa_ecg PRIVATE /bigobj)
endif()

add_executable(executa_testes
    tests/test_main.cpp
    src/ClassificadorECG.cpp
    src/EcgBuffer.cpp
)

target_include_directories(executa_testes PRIVATE
    ${catch2_SOURCE_DIR}/single_include
)

if(MSVC)
    target_compile_options(executa_testes PRIVATE /bigobj)
endif()

enable_testing()
add_test(NAME ecg_tests COMMAND executa_testes WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
