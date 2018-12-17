#include "type.h"

#include "type_def.h"
#include "token.h"

namespace tree {

  unresolved_type::unresolved_type(id_token_vec *_id_vec)
    : id_vec(_id_vec) {}

  unresolved_type::~unresolved_type() {
    delete id_vec;
  }

  std::ostream& operator<<(std::operator& os, const unresolved_type& t) {
    os << "unresolved_type-{"
    os << "id: " << *t.id_vec << std::endl;
    os << "}";
    return os;
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

  std::ostream& operator<<(std::ostream& os, const primative_type& t) {
    os << "primative_type-{" << std::endl;
    os << "p_type: ";
    switch(t.t) {
      case I8:
        os << "I8";
      case U8:
        os << "U8";
      case I16:
        os << "I16";
      case U16:
        os << "U16";
      case I32:
        os << "I32";
      case U32:
        os << "U32";
      case F32:
        os << "F32";
      case I64:
        os << "I64";
      case U64:
        os << "U64";
      case F64:
        os << "F64";
      default:
        os << "unknown";
    }
    os << std::endl << "size: " << t.size() << std::endl;
    os << "}";
    return os;
  }

  pointer_type::pointer_type(type* _t)
    : t(_t) {}

  pointer_type::~pointer_type() {
    delete t;
  }

  std::size_t pointer_type::size() {
    return 8;
  }

  std::ostream& operator<<(std::ostream& os, const pointer_type& t) {
    os << "pointer_type-{" << std::endl;
    os << *t.t << std::endl;
    os << "size: " << t.size() << std::endl << "}";
    return os;
  }


  array_type::array_type(type *_t, int_token *_len)
    : t(_t), len(_len) {}

  array_type::~array_type() {
    delete t;
  }

  std::size_t array_type::size() {
    return len->val * t->size();
  }

  std::ostream& operator<<(std::ostream& os, const array_type& t) {
    os << "array_type-{" << std::endl;
    os << *t.t << std::endl;
    os << "len: " << *t.len << std::endl;
    os << "size: " << t.size;
    return os;
  }

  compound_type::compound_type(type_def *_t_def)
    : t_def(_t_def) {}

  compound_type::~compound_type() {} //dont delete reference

  std::size_t compound_type::size() {
    return t_def->size();
  }

  std::ostream& operator<<(std::ostream& os, const compound_type& t) {
    os << "compound_type-{" << std::endl;
    os << *t.t_def << std::endl;
    os << "size: " << t.size() << std::endl << "}";
    return os;
  }
}
