#pragma once

struct id_token;
struct int_token;
struct float_token;
struct string_token;
struct id_token_vec;

namespace tree {

  struct type;

  struct exp {
    virtual ~exp() {}
  };

  struct scalar_exp : exp {
    virtual ~scalar_exp() {}
  };

  struct int_exp : scalar_exp {
    int_token *val;
    int_exp(int_token*);
    ~int_exp();
  };

  struct float_exp : exp {
    float_token *val;
    float_exp(float_token*);
    ~float_exp();
  };

  struct string_exp : exp {
    string_token *val;
    string_exp(string_token*);
    ~string_exp();
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

  struct id_vec_exp : ref_exp {
    id_token_vec *id_vec;
    id_vec_exp(id_token_vec*);
    ~id_vec_exp();
  };

  struct ref_acc_exp : ref_exp {
    ref_exp *left;
    id_token *right;

    enum REF_OP {
      DOT,
      ARROW,
    } op;

    ref_acc_exp(ref_exp*, id_token*, REF_OP);
    ~ref_acc_exp();
  };

  struct ref_off_exp : ref_exp {
    ref_exp *left;
    scalar_exp *right;

    enum REF_OP {
      PLUS,
      MINUS
    } op;

    ref_off_exp(ref_exp*, scalar_exp*, REF_OP);
    ~ref_off_exp();
  };

  struct acc_exp : ref_exp {
    ref_exp *ref;
    scalar_exp *index;

    acc_exp(ref_exp*, scalar_exp*);
    ~acc_exp();
  };

  struct cast_exp : ref_exp {
    ref_exp *ref;
    type *t;

    cast_exp(ref_exp*, type*);
    ~cast_exp();
  };

}
