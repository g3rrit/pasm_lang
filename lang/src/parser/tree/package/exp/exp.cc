#include "exp.h"

#include "type.h"
#include "var_decl.h"

#include "token.h"

namespace tree {

  int_exp::int_exp(int_token *_val)
    : val(_val) {}

  int_exp::~int_exp() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const int_exp& e) {
    os << "int_exp-{" << std::endl;
    os << *e.val << std::endl;
    os << "}";
    return os;
  }

  float_exp::float_exp(float_token *_val)
    : val(_val) {}

  float_exp::~float_exp() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const float_exp& e) {
    os << "float_exp-{" << std::endl;
    os << *e.val << std::endl;
    os << "}";
    return os;
  }

  string_exp::string_exp(string_token *_val)
    : val(_val) {}

  string_exp::~string_exp() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const string_exp& e) {
    os << "string_exp-{" << std::endl;
    os << *e.val << std::endl;
    os << "}";
    return os;
  }

  infix_scalar_exp::infix_scalar_exp(scalar_exp *_left, scalar_exp *_right, INFIX_OP _op)
    : left(_left), right(_right), op(_op) {}

  infix_scalar_exp::~infix_scalar_exp() {
    delete left;
    delete right;
  }

  std::ostream& operator<<(std::ostream& os, const infix_scalar_exp& e) {
    os << "infix_scalar_exp-{" << std::endl;
    os << "op: ";
    switch(e.op) {
      case PLUS:
        os << "PLUS";
        break;
      case MINUS:
        os << "MINUS";
        break;
      case TIMES:
        os << "TIMES";
        break;
      case DIV:
        os << "DIV";
        break;
      case SHIFT_LEFT:
        os << "SHIFT_LEFT";
        break;
      case SHIFT_RIGHT:
        os << "SHIFT_RIGHT";
        break;
      case AND:
        os << "AND";
      case OR:
        os << "OR";
        break;
      case NOR:
        os << "NOR";
        break;
    }
    os << std::endl;
    os << *e.left << std::endl;
    os << *e.right << std::endl;
    os << "}";
    return os;
  }

  id_exp::id_exp(id_token *_id)
    : id(_id) {}

  id_exp::~id_exp() {
    delete id;
  }

  std::ostream& operator<<(std::ostream& os, const id_exp& e) {
    os << "id_exp-{" << std::endl;
    os << *e.id << std::endl;
    os << "}";
    return os;
  }

  id_vec_exp::id_vec_exp(id_token_vec *_id_vec)
    : id_vec(_id_vec) {}

  id_vec_exp::~id_vec_exp() {
    delete id_vec;
  }

  std::ostream& operator<<(std::ostream& os, const id_vec_exp& e) {
    os << "id_vec_exp-{" << std::endl;
    for(const id_token *id : *e.id_vec) {
      os << *id << std::endl;
    }
    os << "}";
    return os;
  }

  var_exp::var_exp(var_decl *_var)
  : var(_var) {}

  var_exp::~var_exp() {
    delete var;
  }

  std::ostream& operator<<(std::ostream& os, const var_exp& e) {
    os << "var_exp-{" << std::endl;
    os << *e.var << std::endl;
    os << "}";
    return os;
  }

  ref_acc_exp::ref_acc_exp(ref_exp *_left, id_token *_right, REF_OP _op)
  : left(_left), right(_right), op(_op) {}

  ref_acc_exp::~ref_acc_exp() {
    delete left;
    delete right;
  }
  
  std::ostream& operator<<(std::ostream& os, const ref_acc_exp& e) {
    os << "ref_acc_exp-{" << std::endl;
    os << "left: " << *e.left << std::endl;
    os << "right: " << *e.right << std::endl;

    os << "op: ";
    switch(e.op) {
      case DOT:
        os << "DOT";
        break;
      case ARROW:
        os << "ARROW";
        break;
    }
    os << std::endl << "}";
    return os;
  }

  ref_off_exp::ref_off_exp(ref_exp *_left, scalar_exp *_right, REF_OP _op)
  : left(_left), right(_right), op(_op) {}

  ref_off_exp::~ref_off_exp() {
    delete left;
    delete right;
  }

  std::ostream& operator<<(std::ostream& os, const ref_off_exp& e) {
    os << "ref_off_exp-{" << std::endl;
    os << "left: " << *e.left << std::endl;
    os << "right: " << *e.right << std::endl;

    os << "op: ";
    switch(e.op) {
      case PLUS:
        os << "PLUS";
        break;
      case MINUS:
        os << "MINUS";
        break;
    }
    os << std::endl << "}";
    return os;
  }

  acc_exp::acc_exp(ref_exp *_ref, scalar_exp *_index)
  : ref(_ref), index(_index) {}

  acc_exp::~acc_exp() {
    delete ref;
    delete index;
  }

  std::ostream& operator<<(std::ostream& os, const acc_exp& e) {
    os << "acc_exp-{" << std::endl;
    os << "ref: " << *e.ref << std::endl;
    os << "index: " << *e.index << std::endl;
    os << std::endl << "}";
    return os;
  }

  cast_exp::cast_exp(ref_exp *_ref, type *_t)
  : ref(_ref), t(_t) {}

  cast_exp::~cast_exp() {
    delete ref;
    delete t;
  }

  std::ostream& operator<<(std::ostream& os, const cast_exp& e) {
    os << "cast_exp-{" << std::endl;
    os << "ref: " << *e.ref << std::endl;
    os << "type: " << *e.t << std::endl;
    os << std::endl << "}";
    return os;
  }

}
