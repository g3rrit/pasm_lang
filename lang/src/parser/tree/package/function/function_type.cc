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

  std::ostream& operator<<(std::ostream& os, const function_type& f) {
    os << "function_type-{" << std::endl;
    os << "size: " << f.size() << std::endl;
    os << "params-{" << std::endl;
    for(const auto& p : f.params) {
      os << *p.second << std::endl;
    }
    os << "}" << std::endl << "}";
    return os;
  }
}
