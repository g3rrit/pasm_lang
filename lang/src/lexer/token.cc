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
      if(*this->at(i) < *rhs.at(i)) {
        return true;
      } else if(*this->at(i) > *rhs.at(i)) {
        return false;
      }
    }
  }
  return false;
}

id_token_vec::~id_token_vec() {
  for(id_token *elem : *this) {
    delete elem;
  }
}


primary_token::primary_token(int _type) : type(_type) {}

id_token::id_token(char *_val) : primary_token(T_ID), val(_val)  {}

id_token::~id_token() {
  delete val;
}

float_token::float_token(float _val) : primary_token(T_FLOAT), val(_val) {}

string_token::string_token(char *_val) : primary_token(T_STRING), val(_val) {}

string_token::~string_token() {
  delete val;
}

int_token::int_token(int _val) : primary_token(T_INTEGER), val(_val) {}

token::token() : type(T_OTHER) {}

token::token(int _type) : type(_type), vt(val_type::NONE_VAL) {}

token::operator id_token*() {
  if(type != T_ID) {
    throw std::bad_cast();
  }
  id_token *res = new id_token(str_val);
  str_val = 0;
  return res;
}

token::operator float_token*() {
  if(type != T_FLOAT) {
    throw std::bad_cast();
  }
  return new float_token(float_val);
}

token::operator int_token*() {
  if(type != T_INTEGER) {
    throw std::bad_cast();
  }
  return new int_token(int_val);
}

token::operator string_token*() {
  if(type != T_STRING) {
    throw std::bad_cast();
  }
  string_token *res = new string_token(str_val);
  str_val = 0;
  return res;
}
