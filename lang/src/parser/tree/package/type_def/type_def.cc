#include "type_def.h"

#include "var_decl.h"
#include "package.h"
#include "token.h"

namespace tree {

  type_def::type_def(id_token *_id)
    : id(_id) {}

  type_def::~type_def() {
    for(auto elem : *this) {
      delete elem.second;
    }
  }
}
