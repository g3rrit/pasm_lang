#include "var_def.h"

#include <iostream>

#include "var_decl.h"
#include "literal.h"
#include "token.h"

namespace tree {

  var_def::var_def(var_decl *_decl, literal *_lit)
    : decl(_decl), lit(_lit) {
      if(decl == nullptr) {
        std::cerr << "invalid var_decl" << std::endl;
        //TODO: throw error
      }
    }

  var_def::~var_def() {
    delete lit;
    delete decl;
  }

  id_token& var_def::get_id() {
    return decl->get_id();
  }

  std::ostream& operator<<(std::operator& os, const var_def& v) {
    os << "var_def-{" << std::endl;
    os << *v.decl << std::endl;
    os << *v.lit << std::endl;
    os << "}";
    return os;
  }
}
