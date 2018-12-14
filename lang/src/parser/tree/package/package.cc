#include "package.h"

#include "token.h"

#include "function.h"

namespace tree {

  package::package(id_token_vec* _token_vec)
    : token_vec(_token_vec) {
  }

  package::~package() {
    delete token_vec;
  }

  void package::add_function(function* _fun) {
    functions.insert(std::make_pair(_fun->id, _fun));
  }
}
