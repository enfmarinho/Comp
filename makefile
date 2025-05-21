# Tools
CXX = g++
YACC = bison
LEX = flex

# Flags settings
CXXFLAGS = -std=c++17 -I$(BUILD_DIR) -I$(SRC_DIR)
LEXFLAGS = -o $(LEX_OUT)
YACCFLAGS = -d -v -o $(YACC_OUT)

# Directories
SRC_DIR = src
BUILD_DIR = build
$(shell mkdir -p $(BUILD_DIR)) # Ensure build directory exists

# Targets
TARGET = $(BUILD_DIR)/comp
YACC_IN = $(SRC_DIR)/parser.ypp
LEX_IN = $(SRC_DIR)/scanner.l
LEX_OUT = $(BUILD_DIR)/lex.yy.cc
YACC_OUT = $(BUILD_DIR)/parser.tab.cpp
YACC_HDR = $(BUILD_DIR)/parser.tab.hpp
YACC_VERBOSE_FILE = $(BUILD_DIR)/parser.output

SRCS = $(wildcard $(SRC_DIR)/*.cpp) \
       $(LEX_OUT) \
       $(YACC_OUT)

# Object files. First line for cpp files from SRC_DIR, second and third line for the lex and yacc generated files respectively
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp,$(SRCS))) \
       $(patsubst $(BUILD_DIR)/%.cc,$(BUILD_DIR)/%.o,$(filter $(BUILD_DIR)/%.cc,$(SRCS))) \
       $(patsubst $(BUILD_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(BUILD_DIR)/%.cpp,$(SRCS)))

all: $(TARGET)

# Link all objects into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generate parser files from parser.ypp
$(YACC_OUT) $(YACC_HDR): $(YACC_IN)
	$(YACC) $(YACCFLAGS) $(YACC_IN)

# Generate lexer from scanner.l
$(LEX_OUT): $(LEX_IN) $(YACC_HDR)  # Depends on parser header
	$(LEX) $(LEXFLAGS) $(LEX_IN)

# Compile .cpp files from SRC_DIR into BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(YACC_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile .cc files (lexer output) into BUILD_DIR
$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.cc $(YACC_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile parser output into BUILD_DIR
$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.cpp $(YACC_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)/*.o $(YACC_OUT) $(LEX_OUT) $(YACC_HDR) $(YACC_VERBOSE_FILE) $(TARGET)
	rmdir build

.PHONY: all clean
