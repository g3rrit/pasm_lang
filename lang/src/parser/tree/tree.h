#pragma once

#include <string>
#include <map>
#include <vector>

#include "package.h"
#include "util.h"
#include "token.h"

namespace tree {
  struct tree {
      std::map<id_token_vec*, package*, util::cmp_id_token_vec> package_map;

      package* packge_add(id_token_vec*);
      package* package_get(id_token_vec*);
      bool package_exists(id_token_vec*);

  };
}
