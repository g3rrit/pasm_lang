#pragma once

#include "token.h"

namespace util {
  struct cmp_str {
    bool operator()(char const*, char const*) const;
  };

  struct cmp_id_token {
    bool operator()(id_token const*, id_token const*) const;
  };

  struct cmp_id_token_vec {
    bool operator()(id_token_vec const*, id_token_vec const*) const;
  };

}
