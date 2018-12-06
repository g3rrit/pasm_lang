#pragma once

#include <vector>

#include "token.h"

namespace tree {

  struct package {
    id_token_vec *token_vec;

    package(id_token_vec*);

    ~package();
  };

}
