CXX = g++
ONNX_DIR = libs/onnxruntime-linux-x64-1.20.1
CXXFLAGS = -Wall -std=c++17 -Iinclude -I$(ONNX_DIR)/include
LDFLAGS = -L$(ONNX_DIR)/lib -lonnxruntime -Wl,-rpath,$(ONNX_DIR)/lib

TARGET = classificador_ecg
SRC_DIR = src
INC_DIR = include

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/ClassificadorECG.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/ClassificadorECG.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(SIM_OBJS) $(TEST_OBJS)

SIM_TARGET = bin/simulacao
SIM_SRCS = $(SRC_DIR)/simulation.cpp $(SRC_DIR)/ClassificadorECG.cpp
SIM_OBJS = $(SIM_SRCS:.cpp=.o)

simulation: $(SIM_OBJS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(SIM_TARGET) $(SIM_OBJS) $(LDFLAGS)
	./$(SIM_TARGET)

TEST_TARGET = bin/executa_testes
TEST_SRCS = tests/test_main.cpp $(SRC_DIR)/ClassificadorECG.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(LDFLAGS)
	./$(TEST_TARGET)