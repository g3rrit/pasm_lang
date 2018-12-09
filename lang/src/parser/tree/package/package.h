#pragma once

#include <vector>

struct id_token_vec;

namespace tree {

  struct package {
    id_token_vec *token_vec;

    package(id_token_vec*);

    ~package();
  };

}
