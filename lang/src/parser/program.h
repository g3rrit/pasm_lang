#pragma once

#include <vector>
#include <string>

#include "tree.h"

namespace prog {
  struct prog_state {
    tree::tree *t;
  };

  struct prog {
    std::vector<std::string> files;

    tree::tree t;

    prog();
    ~prog();

    void add_file(std::string&);

    void parse();
    void parse_file(void*, prog_state&, std::string& file);

    void resolve();
  };
}
