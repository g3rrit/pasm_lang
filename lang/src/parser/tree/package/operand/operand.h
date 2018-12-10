#pragma once

struct float_token;

namespace tree {

  struct ref_exp;
  struct scalar_exp;

  struct operand {
    virtual ~operand() {}
  };

  struct ref_operand : operand {
    ref_exp *val;
    ref_operand(ref_exp*);
    ~ref_operand();
  };

  struct float_operand : operand {
    float_token *val;
    float_operand(float_token*);
    ~float_operand();
  };

  struct scalar_operand : operand {
    scalar_exp *val;
    scalar_operand(scalar_exp*);
    ~scalar_operand();
  };

  struct acc_operand : operand {
    scalar_exp *val;
    acc_operand(scalar_exp*);
    ~acc_operand();
  };
}
