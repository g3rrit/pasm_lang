#include "function.h"

#include "var_decl.h"
#include "var_def.h"
#include "statement.h"

#include "token.h"

namespace tree {

  function::function(id_token *_id)
    : id(_id) {}

  function::~function() {
    for(auto elem : params) {
      delete elem.first;
    }
    for(auto elem : defs) {
      delete elem.first;
    }
    for(statement *stm : stms) {
      delete stm;
    }
  }

  void function::add_param(var_decl *_param) {
    params.insert(std::make_pair(_param->id, _param));
  }

  void function::add_def(var_def *_def) {
    defs.insert(std::make_pair(_def->decl->id, _def));
  }

  void function::add_stm(statement *_stm) {
    stms.push_back(_stm);
  }
}
