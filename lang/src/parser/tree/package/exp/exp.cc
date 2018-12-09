#include "exp.h"

#include "type.h"

#include "token.h"

namespace tree {

  int_exp::int_exp(int _val)
    : val(_val) {}

  int_exp::~int_exp() {}

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

  infix_ref_exp::infix_ref_exp(ref_exp *_left, ref_exp *_right, REF_OP _op)
    : left(_left), right(_right), op(_op) {}

  infix_ref_exp::~infix_ref_exp() {
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
