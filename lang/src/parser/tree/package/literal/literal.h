#pragma once

#include <ostream>
#include <vector>

namespace tree {

  struct exp;

  struct literal : std::vector<exp*> {
    ~literal();

    friend std::ostream& operator<<(std::ostream&, const literal&);
  };
}
