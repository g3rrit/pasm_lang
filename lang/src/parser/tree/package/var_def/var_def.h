#pragma once

struct id_token;

namespace tree {

  struct var_decl;
  struct literal;

  struct var_def {
    var_decl *decl;
    literal *lit;

    var_def(var_decl*, literal*);
    ~var_def();

    id_token& get_id();
  };
};
