# 1. Configurações
CXX = g++
# Adicionei -Iinclude para o compilador achar o .h na pasta include
CXXFLAGS = -Wall -std=c++11 -Iinclude

TARGET = classificador_ecg

# 2. Caminhos
SRC_DIR = src
INC_DIR = include

# Arquivos fontes
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/ClassificadorECG.cpp
# Isso gera: src/main.o src/ClassificadorECG.o
OBJS = $(SRCS:.cpp=.o)

# 3. Regras
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar cada .cpp em seu respectivo .o
# Agora incluímos o caminho da pasta src e a dependência do header
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/ClassificadorECG.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

TEST_TARGET = bin/executa_testes
TEST_SRCS = tests/test_main.cpp src/ClassificadorECG.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Regra para compilar os testes
test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)
	./$(TEST_TARGET)  # Roda os testes automaticamente após compilar