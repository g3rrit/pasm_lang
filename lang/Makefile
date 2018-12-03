TARGET ?= comp
BUILD ?= ./build

CC := clang++

LEMON := lemon
RE2C := re2c
COPY := cp

SRC := ./src

PARSER := ./parser/grammar.y
PARSER_OUT := ./parser/out

LEXER := ./lexer/lexer.re
LEXER_OUT := ./src/lexer/lexer.cc

LEXER_DIR := ./lexer

SRCS = $(shell find $(SRC) -name *.cc)
OBJS = $(SRCS:%=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS = $(shell find $(SRC) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17

all:
	$(RE2C) --input custom -o $(LEXER_OUT) $(LEXER)
	$(LEMON) -s -d$(PARSER_OUT) $(PARSER)
	$(COPY) $(PARSER_OUT)/grammar.c $(SRC)/parser/parser.cc
	$(COPY) $(PARSER_OUT)/grammar.h $(SRC)/lexer/token_types.h
	$(CC) -std=c++17 -Wall $(INC_FLAGS) $(SRCS) -o $(BUILD)/$(TARGET)
	$(BUILD)/$(TARGET)

debug:
	$(RE2C) --input custom -o $(LEXER_OUT) $(LEXER)
	$(LEMON) -s -d$(PARSER_OUT) $(PARSER)
	$(COPY) $(PARSER_OUT)/grammar.c $(SRC)/parser/parser.cc
	$(COPY) $(PARSER_OUT)/grammar.h $(SRC)/lexer/token_types.h
	$(CC) -std=c++17 -Wall -g $(INC_FLAGS) $(SRCS) -o $(BUILD)/$(TARGET)
	gdb $(BUILD)/$(TARGET)


-include $(DEPS)

MKDIR_P ?= mkdir -p

clean:
	rm $(BUILD)/*
	rm parser/out/*
