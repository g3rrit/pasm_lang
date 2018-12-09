#pragma once

struct id_token;

namespace tree {

  struct type;

  struct exp {
    virtual ~exp() {}
  };

  struct scalar_exp : exp {
    virtual ~scalar_exp() {}
  };

  struct int_exp : exp {
    int val;
    int_exp(int);
    ~int_exp();
  };

  struct infix_scalar_exp : scalar_exp {
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

    infix_scalar_exp(scalar_exp*, scalar_exp*, INFIX_OP);
    ~infix_scalar_exp();
  };

  struct ref_exp : exp {
    virtual ~ref_exp() {}
  };

  struct id_exp : ref_exp {
    id_token *id;
    id_exp(id_token*);
    ~id_exp();
  };

  struct infix_ref_exp : ref_exp {
    ref_exp *left;
    ref_exp *right;

    enum REF_OP {
      ID,
      DOT,
      ARROW,
      PLUS,
      MINUS
    } op;

    infix_ref_exp(ref_exp*, ref_exp*, REF_OP);
    ~infix_ref_exp();
  };

  struct acc_exp : ref_exp {
    ref_exp *ref;
    scalar_exp *index;

    acc_exp(ref_exp*, scalar_exp*);
    ~acc_exp();
  };

  struct cast_exp : exp {
    ref_exp *ref;
    type *t;

    cast_exp(ref_exp*, type*);
    ~cast_exp();
  };

}
