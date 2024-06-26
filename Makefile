CC = g++        # Compiler to use
CFLAGS = -Wall -std=c++23  # Compiler flags for C++23
SRC = src/main.cpp src/APIs/ASCII_ART_API.hpp src/APIs/COLOR_CODING_API.hpp src/Headers/QB_BackEnd.hpp src/Headers/paint.hpp src/Headers/QB_Banners.hpp src/Headers/QB_FrontEnd.hpp
OBJ = $(SRC:.cpp=.o)  # Object files

TARGET = QBCalculator

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
