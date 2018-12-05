#pragma once

#include <string>
#include <map>

#include "package.h"

namespace tree {
  struct tree {
      std::map<std::string, package> package_map;


      void packge_add(std::string name);
      package* package_get(std::string &name);
      bool package_exists(std::string &name);

  };
}
