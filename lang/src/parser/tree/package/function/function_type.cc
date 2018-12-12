#include "function_type.h"

#include "var_decl.h"

namespace tree {

  function_type::~function_type() {
    for(auto elem : params) {
      delete elem.second;
    }
  }

  void function_type::add_param(var_decl *_param) {
    params.insert(std::make_pair(_param->id, _param));
  }

  std::size_t function_type::size() {
    return 8;
  }
}
