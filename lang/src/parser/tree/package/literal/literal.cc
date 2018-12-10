#include "literal.h"

#include "exp.h"

namespace tree {
  literal::~literal() {
    for(exp* e : *this) {
      delete e;
    }
  }
}
