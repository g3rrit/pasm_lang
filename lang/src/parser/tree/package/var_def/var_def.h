#pragma once

namespace tree {

  struct var_decl;
  struct literal;

  struct var_def {
    var_decl *decl;
    literal *lit;

    var_def(var_decl*, literal*);
    ~var_def();
  };
};
