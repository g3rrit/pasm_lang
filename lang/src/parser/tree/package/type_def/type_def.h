#pragma once

#include "util.h"

#include <map>

struct id_token;

namespace tree {

  struct package;

  struct var_decl;

  struct type_def : std::map<id_token*, var_decl*, util::cmp_id_token> {
    id_token *id;

    type_def(id_token*);
    ~type_def();
  };
}
