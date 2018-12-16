#include "compiler.h"

#include <iostream>

namespace comp {

  comp::comp() {}
  comp::~comp() {}

  void comp::start() {
    /* TEST */
    std::string main {"test/main.pasm"};
    p.add_file(main);
    /* ---- */

    p.parse();

    p.print();
  }
}
