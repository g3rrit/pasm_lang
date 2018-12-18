#include "literal.h"

#include "exp.h"

namespace tree {
  literal::~literal() {
    for(exp* e : *this) {
      delete e;
    }
  }

  std::ostream& operator<<(std::ostream& os, const literal& l) {
    os << "literal-{"
    for(exp *e : l) {
      os << *e << std::endl;
    }
    os << "}";
    return os;
  }
}
