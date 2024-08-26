CXX := c++
CXXFLAGS := -Wall -std=c++20

# Include paths
INCLUDES := -I./include -I/opt/homebrew/include 

# Library paths and libraries
LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib 
LDLIBS = -lncurses -lboost_unit_test_framework

# Source directory
SRCDIR := ./src

BUILD_DIR := ./build

# Automatically find all .cpp files and generate corresponding .o file names
GAME_SOURCES := $(shell find $(SRCDIR) -name '*.cpp' -not -name 'test_call.cpp')
GAME_OBJECTS := $(GAME_SOURCES:.cpp=.o)

TEST_SOURCES := $(shell find $(SRCDIR) -name 'test_call.cpp')
TEST_OBJECTS := $(TEST_SOURCES:.cpp=.o)

# Main and test source files
MAIN_SOURCE := $(SRCDIR)/main.cpp
MAIN_OBJECT := $(MAIN_SOURCE:.cpp=.o)

TEST_SOURCE := $(SRCDIR)/test_call.cpp
TEST_OBJECT := $(TEST_SOURCE:.cpp=.o)

# Targets
game: $(GAME_OBJECTS) $(MAIN_OBJECT)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

tests: $(TEST_OBJECTS) $(TEST_OBJECT)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Pattern rule for building .o files from .cpp files, handling subdirectories
%.o: $(BUILD_DIR)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $^ -o $@

# Clean up generated files
clean:
	rm -f game tests $(GAME_OBJECTS) $(TEST_OBJECTS)
