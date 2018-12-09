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


primary_token::primary_token(int _type) : type(_type) {}

id_token::id_token(char *_val) : primary_token(ID), val(_val)  {}

id_token::~id_token() {
  delete val;
}

float_token::float_token(float _val) : primary_token(FLOAT), val(_val) {}

string_token::string_token(char *_val) : primary_token(STRING), val(_val) {}

string_token::~string_token() {
  delete val;
}

int_token::int_token(int _val) : primary_token(INTEGER), val(_val) {}

token::token() : type(OTHER) {}

token::token(int _type) : type(_type), vt(val_type::NONE_VAL) {}

token::operator id_token() {
  if(type != ID) {
    throw std::bad_cast();
  }
  return id_token(str_val);
}

token::operator float_token() {
  if(type != FLOAT) {
    throw std::bad_cast();
  }
  return float_token(float_val);
}

token::operator int_token() {
  if(type != INTEGER) {
    throw std::bad_cast();
  }
  return int_token(int_val);
}

token::operator string_token() {
  if(type != STRING) {
    throw std::bad_cast();
  }
  return string_token(str_val);
}
