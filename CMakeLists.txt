cmake_minimum_required(VERSION 3.10)
project(ClassificadorECG)

# Define onde estão os arquivos .hpp
include_directories(include)

# Cria o executável juntando os arquivos da src
add_executable(programa_ecg src/main.cpp src/ClassificadorECG.cpp)