#pragma once

namespace util {
  struct cmp_str {
    bool operator()(char const*, char const*) const;
  };
}
