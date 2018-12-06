#include "package.h"

namespace tree {

  package::package(id_token_vec* _token_vec)
    : token_vec(_token_vec) {
  }

  package::~package() {
    delete token_vec;
  }

}
