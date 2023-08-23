CXX := g++
CXXFLAGS := -std=c++17

# Directory for GoogleTest source code
GTEST_DIR := googletest/googletest

# Directory for the project source files
SRC_DIR := src
OBJ_DIR := obj

# Add necessary includes and libraries here
INCLUDES := -I$(GTEST_DIR)/include
LDFLAGS := -L$(GTEST_DIR)/make
LDLIBS := -lgtest_main -lgtest -lpthread

# Test target executable
TARGET := CS251Proj2

# Add your source files to this list
SRCS := main.cpp
OBJS := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(TARGET)
