#pragma once

#include "token.h"

namespace tree {

  struct type;

  struct exp {

  };

  struct scalar_exp : exp {

  };

  struct int_exp : exp {
    int val;
  };

  struct infix_exp : scalar_exp {
    scalar_exp *left;
    scalar_exp *right;
    enum INFIX_OP {
      PLUS,
      MINUS,
      TIMES,
      DIV,
      MOD,
      SHIFT_LEFT,
      SHIFT_RIGHT,
      AND,
      OR,
      NOR
    } op;

    infix_exp(scalar_exp*, scalar_exp*, INFIX_OP);
  }

  struct ref_exp : exp {

  };

  struct id_exp : ref_exp {
    id_token id;
  };

  struct acc_exp : ref_exp {
    ref_exp *ref;
    scalar_exp *index;

    acc_exp(ref_exp*, scalar_exp*);
  };

  struct cast_exp : exp {
    ref_exp *ref;
    type *t;

    cast_exp(ref_exp*, type*);
  };

}
