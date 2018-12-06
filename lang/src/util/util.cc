#include "util.h"

#include <cstring>

namespace util {
  bool cmp_str::operator()(const char *a, const char *b) const {
    return std::strcmp(a, b) < 0;
  }


  bool cmp_id_token_vec::operator()(id_token_vec const* a, id_token_vec const* b) const {
    return *a < *b;
  }
}
