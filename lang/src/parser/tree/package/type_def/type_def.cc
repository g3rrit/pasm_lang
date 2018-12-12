#include "type_def.h"

#include "var_decl.h"
#include "package.h"
#include "token.h"

namespace tree {

  type_def::type_def(id_token *_id)
    : id(_id) {}

  type_def::~type_def() {
    for(auto elem : elems) {
      delete elem.second;
    }
  }

  std::size_t type_def::size() {
    std::size_t s = 0;
    for(auto elem : elems) {
      s += elem.second->size();
    }
    return s;
  }

  void type_def::add_elem(var_decl *_elem) {
    elems.insert(std::make_pair(_elem->id, _elem));
  }
}
