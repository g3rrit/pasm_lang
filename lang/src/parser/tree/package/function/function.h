#pragma once

#include <vector>
#include <map>
#include "util.h"

struct id_token;

namespace tree {

  struct function_type;
  struct var_def;
  struct var_decl;
  struct statement;

  struct function {
    id_token *id;
    function_type *f_type;
    std::map<id_token*, var_def*, util::cmp_id_token> defs;
    std::vector<statement*> stms;

    function(id_token*, function_type*);
    ~function();

    void add_param(var_decl*);
    void add_def(var_def*);
    void add_stm(statement*);
  };

}
