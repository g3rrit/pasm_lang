#pragma once

#include <cstddef>
#include <ostream>

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

    friend std::ostream& operator<<(std::operator&, const var_decl&);
  };
}
