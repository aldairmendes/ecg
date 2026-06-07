cmake_minimum_required(VERSION 3.14)
project(ClassificadorECG CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── ONNX Runtime ─────────────────────────────────────────────────────────
set(ONNX_DIR "${CMAKE_SOURCE_DIR}/libs/onnxruntime-linux-x64-1.20.1")

find_library(ONNX_LIB onnxruntime PATHS "${ONNX_DIR}/lib" NO_DEFAULT_PATH)
if(NOT ONNX_LIB)
    message(FATAL_ERROR "onnxruntime não encontrada em ${ONNX_DIR}/lib")
endif()

include_directories(include "${ONNX_DIR}/include")

# Fontes compartilhadas entre todos os targets
set(SHARED_SRCS
    src/ClassificadorECG.cpp
    src/EcgBuffer.cpp
)

# ─── Executável principal ─────────────────────────────────────────────────
add_executable(programa_ecg
    src/main.cpp
    src/SerialPort.cpp
    ${SHARED_SRCS}
)
target_link_libraries(programa_ecg "${ONNX_LIB}")
set_target_properties(programa_ecg PROPERTIES
    BUILD_RPATH "${ONNX_DIR}/lib"
)

# ─── Simulação ────────────────────────────────────────────────────────────
add_executable(simulacao
    src/simulation.cpp
    ${SHARED_SRCS}
)
target_link_libraries(simulacao "${ONNX_LIB}")
set_target_properties(simulacao PROPERTIES
    BUILD_RPATH "${ONNX_DIR}/lib"
)

# ─── Testes (Catch2 header-only) ─────────────────────────────────────────
add_executable(executa_testes
    tests/test_main.cpp
    ${SHARED_SRCS}
)
target_link_libraries(executa_testes "${ONNX_LIB}")
set_target_properties(executa_testes PROPERTIES
    BUILD_RPATH "${ONNX_DIR}/lib"
)