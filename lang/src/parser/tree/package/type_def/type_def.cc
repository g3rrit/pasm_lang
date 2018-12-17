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

  id_token& type_def::get_id() {

    return *id;
  }

  std::ostream& operator<<(std::ostream& os, const type_def& t) {
    os << "type_def-{" << std::endl;
    os << "id: " << t.get_id() << std::endl;
    os << "size: " << t.size() << std::endl;
    os << "elems-{" << std::endl;
    for(const auto *elem : t.elems) {
      os << *elem.second << std::endl;
    }
    os << "}";
    return os;
  }
}
