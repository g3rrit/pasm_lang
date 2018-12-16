#include "function.h"

#include <iostream>

#include "var_decl.h"
#include "var_def.h"
#include "statement.h"
#include "function_type.h"

#include "token.h"

namespace tree {

  function::function(id_token *_id, function_type *_f_type)
    : id(_id), f_type(_f_type) {
      if(id == nullptr) {
        std::cerr << "invalid id token" << std::endl;
        //TODO: throw error
      }
    }

  function::~function() {
    for(auto elem : defs) {
      delete elem.second;
    }
    for(statement *stm : stms) {
      delete stm;
    }
    delete f_type;
  }

  void function::add_param(var_decl *_param) {
    f_type->add_param(_param);
  }

  void function::add_def(var_def *_def) {
    defs.insert(std::make_pair(_def->decl->id, _def));
  }

  void function::add_stm(statement *_stm) {
    stms.push_back(_stm);
  }

  id_token& function::get_id() {
    return *id;
  }

  std::ostream& operator<<(std::ostream& os, const function &f) {
    os << "function-{" << std::endl;
    os << *f.id << std::endl;
    os << *f.f_type << std::endl;
    os << "defs-{" << std::endl;
    for(const auto *d : f.defs) {
      os << *d.second << std::endl;
    }
    os << "}" << std::endl << "statements-{" << std::endl;
    for(const statement *s : f.stms) {
      os << *s << std::endl;
    }
    os << "}" << std::endl;

    return os;
  }
}
