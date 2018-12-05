#include "tree.h"

namespace tree {

  void tree::packge_add(char* name) {
    package_map.insert(std::make_pair(name, package(name)));
  }

  package* tree::package_get(char *name) {
    return &package_map.at(name);
  }

  bool tree::package_exists(char *name) {
    return package_map.count(name);
  }

}
