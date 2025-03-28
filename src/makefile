# Tools
CXX = clang++
YACC = bison
LEX = flex

# Flags settings
CXXFLAGS = -std=c++17 
LEXFLAGS = -o $(LEX_OUT)
YACCFLAGS = -d -v -o $(YACC_OUT)

# Targets
TARGET = comp
YACC_IN = parser.ypp
LEX_IN = scanner.l
LEX_OUT = lex.yy.cc
YACC_OUT = parser.tab.cpp
YACC_HDR = parser.tab.hpp
YACC_VERBOSE_FILE = parser.output

# Source files
SRCS = main.cpp \
       $(LEX_OUT) \
       $(YACC_OUT)

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.cc=.o)

# Default rule
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

%.o: %.cpp $(YACC_HDR) # Ensure parser header is ready
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.cc $(YACC_HDR) # Ensure parser header is ready
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean generated files
clean:
	rm -f $(TARGET) $(OBJS) $(LEX_OUT) $(YACC_OUT) $(YACC_HDR) $(YACC_VERBOSE_FILE)

.PHONY: all clean
