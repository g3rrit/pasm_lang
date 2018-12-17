#pragma once

#include "util.h"
#include <cstddef>
#include <ostream>
#include <map>

struct id_token;

namespace tree {

  struct package;

  struct var_decl;

  struct type_def {
    id_token *id;
    std::map<id_token*, var_decl*, util::cmp_id_token> elems;

    type_def(id_token*);
    ~type_def();

    std::size_t size();

    void add_elem(var_decl*);

    id_token& get_id();

    friend std::ostream& operator<<(std::ostream&, const type_def&);
  };
}
