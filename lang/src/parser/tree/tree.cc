#include "tree.h"

#include "token.h"
#include "package.h"

namespace tree {

  package* tree::packge_add(id_token_vec* token_vec) {
    package *p = new package(token_vec);
    package_map.insert(std::make_pair(token_vec, p));
    return p;
  }

  package* tree::package_get(id_token_vec* token_vec) {
    return package_map.at(token_vec);
  }

  bool tree::package_exists(id_token_vec* token_vec) {
    return package_map.count(token_vec);
  }

  std::ostream& operator<<(std::ostream& os, const tree &t) {
    os << "syntax tree-{" << std::endl;
    os << "packages-{" << std::endl;
    for(auto *p : t.package_map) {
      os << *p.second << std::endl
    }

    os << "}" << std::endl << "}";
    return os;
  }
}
