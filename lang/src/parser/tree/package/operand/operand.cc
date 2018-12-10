#include "operand.h"

#include "exp.h"
#include "token.h"

namespace tree {

  ref_operand::ref_operand(ref_exp* _val)
    : val(_val) {}

  ref_operand::~ref_operand() {
    delete val;
  }

  float_operand::float_operand(float_token *_val)
    : val(_val) {}

  float_operand::~float_operand() {
    delete val;
  }

  scalar_operand::scalar_operand(scalar_exp *_val)
    : val(_val) {}

  scalar_operand::~scalar_operand() {
    delete val;
  }

  acc_operand::acc_operand(scalar_exp *_val)
    : val(_val) {}

  acc_operand::~acc_operand() {
    delete val;
  }
}
