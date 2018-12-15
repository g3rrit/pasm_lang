#pragma once

#include <cstddef>

struct id_token;

namespace tree {

  struct type;

  struct var_decl {
    id_token *id;
    type *t;

    var_decl(id_token*, type*);
    ~var_decl();

    std::size_t size();

    id_token& get_id();
  };
}
