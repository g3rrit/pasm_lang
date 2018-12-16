#include "package.h"

#include <iostream>

#include "token.h"

#include "function.h"
#include "var_def.h"
#include "var_decl.h"
#include "type_def.h"

namespace tree {

  package::package(id_token_vec* _ids)
    : ids(_ids) {
      if(_ids == nullptr) {
        std::cerr << "invalid package name" << std::endl;
        //TODO: throw error
      }
  }

  package::~package() {
    delete ids;
  }

  void package::add_function(function* _fun) {
    functions.insert(std::make_pair(&_fun->get_id(), _fun));
  }

  void package::add_var_def(var_def *_def) {
    var_defs.insert(std::make_pair(&_def->get_id(), _def));
  }

  void package::add_var_decl(var_decl *_decl) {
    var_decls.insert(std::make_pair(&_decl->get_id(), _decl));
  }

  void package::add_type(type_def *_type) {
    types.insert(std::make_pair(&_type->get_id(), _type));
  }

  id_token_vec& package::get_ids() {
    return *ids;
  }

  std::ostream& operator<<(std::ostream& os, const package &p) {
    os << "package-{" << std::endl;
    os << "functions-{" << std::endl;
    for(const auto *f : p.functions) {
      os << *f.second << std::endl;
    }
    os << "}" << std::endl << "var_defs-{" << std::endl;
    for(const auto *v : p.var_defs) {
      os << *v.second << std::endl;
    }
    os << "}" << std::endl << "var_decls-{" << std::endl;
    for(const auto *v : p.var_decls) {
      os << *v.second << std::endl;
    }
    os << "}" << std::endl << "types-{" << std::endl;
    for(const auto *t : p.types) {
      os << *t.second << std::endl;
    }
    os << "}" << std::endl << "}";
    return os;
  }
}
