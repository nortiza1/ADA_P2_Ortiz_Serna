CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS += -Iinclude

BUILD := build
LIB   := $(BUILD)/numero.o $(BUILD)/multiplicacion.o

.PHONY: all test bench clean

all: $(BUILD)/validacion $(BUILD)/benchmark

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: src/%.cpp include/numero.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/validacion: tests/validacion.cpp $(LIB)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

$(BUILD)/benchmark: bench/benchmark.cpp $(LIB)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

test: $(BUILD)/validacion
	./$(BUILD)/validacion

bench: $(BUILD)/benchmark
	mkdir -p resultados
	./$(BUILD)/benchmark

clean:
	rm -rf $(BUILD)
