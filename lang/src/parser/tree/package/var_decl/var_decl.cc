#include "var_decl.h"

#include "type.h"
#include "token.h"

namespace tree {

  var_decl::var_decl(id_token *_id, type *_t)
    : id(_id), t(_t) {}

  var_decl::~var_decl() {
    delete t;
  }
}
