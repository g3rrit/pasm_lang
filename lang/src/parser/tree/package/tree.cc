#include "tree.h"

namespace tree {

  void tree::packge_add(std::string name) {
    package_map.insert(std::pair<std::string, package>(name, package(name)));
  }

  package* tree::package_get(std::string &name) {
    return &package_map.at(name);
  }

  bool tree::package_exists(std::string &name) {
    return package_map.count(name);
  }

}
