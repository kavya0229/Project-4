CC=gcc
CXX=g++

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
TEST_SRC_DIR = ./testsrc

CXXFLAGS = -std=c++17 -I$(INC_DIR)
LDFLAGS = -lgtest -lpthread -lexpat -Igtest_main

# Source and Object Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Test Source and Object Files
TEST_SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRC_FILES))
TEST_BINS := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(TEST_SRC_FILES))

# Phony targets for building and cleaning the project
.PHONY: all directories runtests clean

all: directories runtests

runtests: $(TEST_BINS)
	@for test_bin in $^ ; do \
		$$test_bin ; \
	done

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test source files to object files
$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create test binaries
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)