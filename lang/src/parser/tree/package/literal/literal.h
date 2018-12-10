#pragma once

#include <vector>

namespace tree {

  struct exp;

  struct literal : std::vector<exp*> {
    ~literal();
  };
}
