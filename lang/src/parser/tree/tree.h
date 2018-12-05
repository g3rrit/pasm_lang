#pragma once

#include <string>
#include <map>

#include "package.h"
#include "util.h"

namespace tree {
  struct tree {
      std::map<char*, package, util::cmp_str> package_map;

      void packge_add(char*);
      package* package_get(char*);
      bool package_exists(char*);

  };
}
