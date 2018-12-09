#pragma once

struct id_token;

namespace tree {

  struct type;

  struct var_decl {
    id_token *id;
    type *t;

    var_decl(id_token*, type*);
    ~var_decl();
  };
}
