CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I. -Isrc/app/encryptDecrypt -IfileHandling -Iprocesses

# Target executable
TARGET = encrypt_decrypt

# Source files
SRC = main.cpp \
      src/app/processes/ProcessManagement.cpp \
      src/app/fileHandling/IO.cpp \
      src/app/fileHandling/ReadEnv.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Cryption object file
CRYPTION_OBJ = src/app/encryptDecrypt/Cryption.o

# Rule to build the target
$(TARGET): $(OBJ) $(CRYPTION_OBJ)
	$(CXX) $(OBJ) $(CRYPTION_OBJ) -o $(TARGET)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build Cryption.o
$(CRYPTION_OBJ):
	$(MAKE) -C src/app/encryptDecrypt

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)
	$(MAKE) -C src/app/encryptDecrypt/cryption clean

# Phony targets
.PHONY: clean
