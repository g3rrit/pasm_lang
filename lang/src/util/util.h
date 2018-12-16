#pragma once

#include "token.h"
#include "iostream"

#define DEBUG

#ifdef DEBUG

#define log_debug(msg) \
  std::cout << "log: " << msg << std::endl;

#else

#define log_debug(msg) \
  ;

#endif



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
