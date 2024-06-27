CXX = g++

CXXFLAGS = -std=c++23

SRC_DIR = src

INC_DIR = $(SRC_DIR)/Headers

API_DIR = $(SRC_DIR)/APIs

TARGET = QBCalculator.exe

SRCS = $(SRC_DIR)/main.cpp \
       $(API_DIR)/ASCII_ART_API.hpp \
       $(API_DIR)/COLOR_CODING_API.hpp \
       $(INC_DIR)/QB_BackEnd.hpp \
       $(INC_DIR)/paint.hpp \
       $(INC_DIR)/QB_Banners.hpp \
       $(INC_DIR)/QB_FrontEnd.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)
	@echo Done... Now You Can Run The App

$(TARGET): $(OBJS)
	@echo Linking Headers And Libraries..... This Will Take Some More Time !!
	@$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	@echo Building App....
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
.PHONY: all clean
