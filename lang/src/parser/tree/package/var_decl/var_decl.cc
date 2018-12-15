#include "var_decl.h"

#include <iostream>

#include "type.h"
#include "token.h"

namespace tree {

  var_decl::var_decl(id_token *_id, type *_t)
    : id(_id), t(_t) {
      if(id == nullptr) {
        std::cerr << "invalid id token" << std::endl;
        //TODO: throw error
      }
    }

  var_decl::~var_decl() {
    delete t;
  }

  std::size_t var_decl::size() {
    return t->size();
  }

  id_token& var_decl::get_id() {
    return *id;
  }
}
