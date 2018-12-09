#include "var_def.h"

#include "var_decl.h"
#include "literal.h"

namespace tree {

  var_def::var_def(var_decl *_decl, literal *_lit)
    : decl(_decl), lit(_lit) {}

  var_def::~var_def() {
    delete lit;
    delete decl;
  }
}
