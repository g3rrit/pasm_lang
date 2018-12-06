#include "token.h"

#include <cstring>

std::string token::get_str() const {
  switch(this->type) {
    default:
      return "UNDEFINED";
  }
}

bool id_token::operator<(const id_token& rhs) const {
  return std::strcmp(this->val, rhs.val) < 0;
}

bool id_token::operator>(const id_token& rhs) const {
  return std::strcmp(this->val, rhs.val) > 0;
}

bool id_token_vec::operator<(const id_token_vec& rhs) const {
  size_t lhs_size = this->size();
  size_t rhs_size = rhs.size();
  if(lhs_size < rhs_size) {
    return true;
  } else if(lhs_size > rhs_size) {
    return false;
  } else {
    for(size_t i = 0; i < lhs_size; i++) {
      if(this->at(i) < rhs.at(i)) {
        return true;
      } else if(this->at(i) > rhs.at(i)) {
        return false;
      }
    }
  }
  return false;
}
