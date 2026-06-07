CXX      = g++
ONNX_DIR = libs/onnxruntime-linux-x64-1.20.1
CXXFLAGS = -Wall -std=c++17 -Iinclude -I$(ONNX_DIR)/include
LDFLAGS  = -L$(ONNX_DIR)/lib -lonnxruntime -Wl,-rpath,$(ONNX_DIR)/lib

SRC_DIR  = src
INC_DIR  = include
BIN_DIR  = bin

# ─── Executável principal (leitura Serial do ESP32) ────────────────────────
TARGET = $(BIN_DIR)/programa_ecg
SRCS   = $(SRC_DIR)/main.cpp \
         $(SRC_DIR)/ClassificadorECG.cpp \
         $(SRC_DIR)/EcgBuffer.cpp \
         $(SRC_DIR)/SerialPort.cpp
OBJS   = $(SRCS:.cpp=.o)

all: $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# ─── Simulação com CSV MIT-BIH ─────────────────────────────────────────────
SIM_TARGET = $(BIN_DIR)/simulacao
SIM_SRCS   = $(SRC_DIR)/simulation.cpp \
             $(SRC_DIR)/ClassificadorECG.cpp \
             $(SRC_DIR)/EcgBuffer.cpp
SIM_OBJS   = $(SIM_SRCS:.cpp=.o)

simulation: $(BIN_DIR) $(SIM_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SIM_TARGET) $(SIM_OBJS) $(LDFLAGS)
	./$(SIM_TARGET)

# ─── Testes (Catch2) ───────────────────────────────────────────────────────
TEST_TARGET = $(BIN_DIR)/executa_testes
TEST_SRCS   = tests/test_main.cpp \
              $(SRC_DIR)/ClassificadorECG.cpp \
              $(SRC_DIR)/EcgBuffer.cpp
TEST_OBJS   = $(TEST_SRCS:.cpp=.o)

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(BIN_DIR) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(LDFLAGS)
	./$(TEST_TARGET)

# ─── Regra genérica de compilação ─────────────────────────────────────────
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ─── Limpeza ───────────────────────────────────────────────────────────────
clean:
	rm -f $(OBJS) $(SIM_OBJS) $(TEST_OBJS) \
	      $(TARGET) $(SIM_TARGET) $(TEST_TARGET)

.PHONY: all simulation test clean