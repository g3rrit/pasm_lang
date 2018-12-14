#pragma once

#include <vector>
#include <map>

#include "util.h"

struct id_token_vec;

namespace tree {

  struct function;

  struct package {
    id_token_vec *token_vec;
    std::map<id_token*, function*, util::cmp_id_token> functions;

    package(id_token_vec*);
    ~package();

    void add_function(function*);
  };

}
