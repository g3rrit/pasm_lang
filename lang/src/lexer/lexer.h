#pragma once

#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>


#include "toke.h"
#include "token_types.h"

token& lex(std::ifstream &in, bool keep);
