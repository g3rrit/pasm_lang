#pragma once

#include <map>
#include <ostream>
#include "util.h"

#include "type.h"

struct id_token;

namespace tree {

  struct var_decl;

  struct function_type : type{
    std::map<id_token*, var_decl*, util::cmp_id_token> params;

    ~function_type();

    void add_param(var_decl* _param);

    std::size_t size();

    friend std::ostream& operator<<(std::ostream&, const function_type&);
  };
}
