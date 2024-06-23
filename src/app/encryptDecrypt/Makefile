# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I../processes -I../fileHandling -std=c++17 -Wall

# Target executable
TARGET = cryption

# Source files
SRC = Cryption.cpp ../fileHandling/ReadEnv.cpp ../fileHandling/IO.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Rule to build the target
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
