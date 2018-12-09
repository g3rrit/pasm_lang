#pragma once

#include <string>
#include <map>
#include <vector>

#include "util.h"

struct id_token_vec;

namespace tree {

  struct package;

  struct tree {
      std::map<id_token_vec*, package*, util::cmp_id_token_vec> package_map;

      package* packge_add(id_token_vec*);
      package* package_get(id_token_vec*);
      bool package_exists(id_token_vec*);

  };
}
