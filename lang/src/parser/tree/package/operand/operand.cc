#include "operand.h"

#include "exp.h"
#include "token.h"

namespace tree {

  ref_operand::ref_operand(ref_exp* _val)
    : val(_val) {}

  ref_operand::~ref_operand() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const ref_operand& o) {
    os << "ref_operand-{" << std::endl;
    os << *o.val << std::endl;
    os << "}";
    return os;
  }

  float_operand::float_operand(float_token *_val)
    : val(_val) {}

  float_operand::~float_operand() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const float_operand& o) {
    os << "float_operand-{" << std::endl;
    os << *o.val << std::endl;
    os << "}";
    return os;
  }

  scalar_operand::scalar_operand(scalar_exp *_val)
    : val(_val) {}

  scalar_operand::~scalar_operand() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const scalar_operand& o) {
    os << "scalar_operand-{" << std::endl;
    os << *o.val;
    os << "}";
    return os;
  }

  acc_operand::acc_operand(scalar_exp *_val)
    : val(_val) {}

  acc_operand::~acc_operand() {
    delete val;
  }

  std::ostream& operator<<(std::ostream& os, const acc_operand& o) {
    os << "acc_operand-{"
    os << *o.val;
    os << "}";
    return os;
  }
}
