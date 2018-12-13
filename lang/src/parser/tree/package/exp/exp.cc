#include "exp.h"

#include "type.h"

#include "token.h"

namespace tree {

  int_exp::int_exp(int_token *_val)
    : val(_val) {}

  int_exp::~int_exp() {
    delete val;
  }

  float_exp::float_exp(float_token *_val)
    : val(_val) {}

  float_exp::~float_exp() {
    delete val;
  }

  string_exp::string_exp(string_token *_val)
    : val(_val) {}

  string_exp::~string_exp() {
    delete val;
  }

  infix_scalar_exp::infix_scalar_exp(scalar_exp *_left, scalar_exp *_right, INFIX_OP _op)
    : left(_left), right(_right), op(_op) {}

  infix_scalar_exp::~infix_scalar_exp() {
    delete left;
    delete right;
  }

  id_exp::id_exp(id_token *_id)
    : id(_id) {}

  id_exp::~id_exp() {
    delete id;
  }

  id_vec_exp::id_vec_exp(id_token_vec *_id_vec)
    : id_vec(_id_vec) {}

  id_vec_exp::~id_vec_exp() {
    delete id_vec;
  }

  ref_acc_exp::ref_acc_exp(ref_exp *_left, id_token *_right, REF_OP _op)
    : left(_left), right(_right), op(_op) {}

  ref_acc_exp::~ref_acc_exp() {
    delete left;
    delete right;
  }

  ref_off_exp::ref_off_exp(ref_exp *_left, scalar_exp *_right, REF_OP _op)
   : left(_left), right(_right), op(_op) {}

  ref_off_exp::~ref_off_exp() {
    delete left;
    delete right;
  }

  acc_exp::acc_exp(ref_exp *_ref, scalar_exp *_index)
   : ref(_ref), index(_index) {}

  acc_exp::~acc_exp() {
    delete ref;
    delete index;
  }

  cast_exp::cast_exp(ref_exp *_ref, type *_t)
    : ref(_ref), t(_t) {}

  cast_exp::~cast_exp() {
    delete ref;
    delete t;
  }
}
