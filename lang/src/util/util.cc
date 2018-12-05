#include "util.h"

#include <cstring>

namespace util {
  bool cmp_str::operator()(const char *a, const char *b) const {
    return std::strcmp(a, b) < 0;
  }
}
