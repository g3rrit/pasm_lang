#pragma once

#include <vector>
#include <map>
#include <ostream>

#include "util.h"

struct id_token_vec;

namespace tree {

  struct function;
  struct var_def;
  struct var_decl;
  struct type_def;

  struct package {
    id_token_vec *ids;
    std::map<id_token*, function*, util::cmp_id_token> functions;
    std::map<id_token*, var_def*, util::cmp_id_token> var_defs;
    std::map<id_token*, var_decl*, util::cmp_id_token> var_decls;
    std::map<id_token*, type_def*, util::cmp_id_token> types;


    package(id_token_vec*);
    ~package();

    void add_function(function*);
    void add_var_def(var_def*);
    void add_var_decl(var_decl*);
    void add_type(type_def*);

    id_token_vec& get_ids();

    friend std::ostream& operator<<(std::ostream&, const package&);
  };

}
