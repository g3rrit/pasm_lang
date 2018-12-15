#include "program.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "token.h"
#include "parser.h"
#include "lexer.h"

namespace prog {

  prog::prog() {}

  prog::~prog() {}

  void prog::add_file(std::string& file) {
    files.push_back(std::move(file));
  }

  void prog::parse() {
    void *parser = parser_alloc();;
    prog_state p_state = {
      .t = &t
    };

    std::cout << "+----------------------------------+" << std::endl;
    for(std::string& file : files) {
      std::cout << "| Parsing file: " << file << std::left << std::setw(20) << "|";
      parse_file(parser, p_state, file);
      std::cout << "\r";
    }
    std::cout << "| Parsing done                     |" << std::endl;
    std::cout << "+----------------------------------+" << std::endl;

    parser_free(parser);
  }

  void prog::parse_file(void *parser, prog_state& p_state, std::string& file) {
    std::ifstream in(file, std::ios::binary);
    if(in.fail()) {
      std::cerr << "unable to open file" << std::endl;
      std::exit(-1);
    }

    token *t = nullptr;
    bool keep = true;
    for(;;) {
      t = lex(in, keep);

      if(t->type == T_OTHER) {
        keep = false;
        continue;
      } else if(t->type == T_END) {
        return;
      }

      keep = true;

      std::cout << t << std::endl;

      parser_parse(parser, t->type, t, &p_state);
    }

  }

  void prog::resolve() {

  }
}
