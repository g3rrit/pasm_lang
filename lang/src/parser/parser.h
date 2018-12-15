#pragma once

#include <cstdlib>

struct token;
namespace prog {
  struct prog_state;
}

void *FParseAlloc(void* (*)(std::size_t));
void FParse(void*, int, token*, prog::prog_state*);
void FParseFree(void*, void(*)(void*));

#define parser_alloc() FParseAlloc(std::malloc)
#define parser_parse(_parser, _type, _value, _state) FParse(_parser, _type, _value, _state)
#define parser_free(_parser) FParseFree(_parser, std::free)
