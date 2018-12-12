#include "type.h"

#include "type_def.h"
#include "token.h"

namespace tree {

  unresolved_type::unresolved_type(id_token *_id)
    : id(_id) {}

  unresolved_type::~unresolved_type() {
    delete id;
  }

  primative_type::primative_type(p_type _t)
    : t(_t) {}

  primative_type::~primative_type() {}

  std::size_t primative_type::size() {
    switch(t) {
      case I8:
      case U8:
        return 1;
      case I16:
      case U16:
        return 2;
      case I32:
      case U32:
      case F32:
        return 4;
      case I64:
      case U64:
      case F64:
        return 8;
      default:
        return 0;
    }
  }

  pointer_type::pointer_type(type* _t)
    : t(_t) {}

  pointer_type::~pointer_type() {
    delete t;
  }

  std::size_t pointer_type::size() {
    return 8;
  }

  array_type::array_type(type *_t, int_token *_len)
    : t(_t), len(_len) {}

  array_type::~array_type() {
    delete t;
  }

  std::size_t array_type::size() {
    return len->val * t->size();
  }

  compound_type::compound_type(type_def *_t_def)
    : t_def(_t_def) {}

  compound_type::~compound_type() {} //dont delete reference

  std::size_t compound_type::size() {
    return t_def->size();
  }
}
