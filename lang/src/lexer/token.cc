#include "token.h"

#include <cstring>

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

std::ostream& operator<<(std::ostream& os, const id_token_vec& t) {
  os << "id_token_vec-{" << std::endl;
  for(const id_token *id : *this) {
    os << *id << std::endl;
  }
  os << "}";
  return os;
}

primary_token::primary_token(int _type) : type(_type) {}

id_token::id_token(char *_val) : primary_token(T_ID), val(_val)  {}

id_token::~id_token() {
  delete val;
}

std::ostream& operator<<(std::ostream& os, const id_token& t) {
  os << "id[" << t.val << "]";
  return os;
}

float_token::float_token(float _val) : primary_token(T_FLOAT), val(_val) {}

std::ostream& operator<<(std::ostream& os, const float_token& t) {
  os << "float[" << t.val << "]";
  return os;
}

string_token::string_token(char *_val) : primary_token(T_STRING), val(_val) {}

string_token::~string_token() {
  delete val;
}

std::ostream& operator<<(std::ostream& os, const string_token& t) {
  os << "string[" << t.val << "]";
  return os;
}

int_token::int_token(int _val) : primary_token(T_INTEGER), val(_val) {}

std::ostream& operator<<(std::ostream& os, const int_token& t) {
  os << "int[" << t.val << "]";
  return os;
}

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
  float new_val = float_val;
  return new float_token(new_val);
}

token::operator int_token*() {
  if(type != T_INTEGER) {
    throw std::bad_cast();
  }
  int new_val = int_val;
  return new int_token(new_val);
}

token::operator string_token*() {
  if(type != T_STRING) {
    throw std::bad_cast();
  }
  string_token *res = new string_token(str_val);
  str_val = 0;
  return res;
}


std::string token::get_str() const {
  switch(this->type) {
    case T_WHITESPACE:
    return "T_WHITESPACE";
    case T_END:
    return "T_END";
    case T_OTHER:
    return "T_OTHER";
    case T_TAB:
    return "T_TAB";
    case T_NEW_LINE:
    return "T_NEW_LINE";
    case T_CARRIAGE_RETURN:
    return "T_CARRIAGE_RETURN";
    case T_CHAR:
    return "T_CHAR";
    case T_MULTICHAR:
    return "T_MULTICHAR";
    case T_LINE_COMMENT:
    return "T_LINE_COMMENT";
    case T_MULTILINE_COMMENT:
    return "T_MULTILINE_COMMENT";
    case T_INTEGER:
    return "T_INTEGER";
    case T_FLOAT:
    return "T_FLOAT";
    case T_STRING:
    return "T_STRING";
    case T_USE:
    return "T_USE";
    case T_AS:
    return "T_AS";
    case T_RET:
    return "T_RET";
    case T_U8:
    return "T_U8";
    case T_U16:
    return "T_U16";
    case T_U32:
    return "T_U32";
    case T_U64:
    return "T_U64";
    case T_I8:
    return "T_I8";
    case T_I16:
    return "T_I16";
    case T_I32:
    return "T_I32";
    case T_I64:
    return "T_I64";
    case T_F32:
    return "T_F32";
    case T_F64:
    return "T_F64";
    case T_EXCALAMATIONMARK_EQUALS:
    return "T_EXCALAMATIONMARK_EQUALS";
    case T_PACKAGE:
    return "T_PACKAGE";
    case T_COLON:
    return "T_COLON";
    case T_SEMICOLON:
    return "T_SEMICOLON";
    case T_EXCLAMATIONMARK:
    return "T_EXCLAMATIONMARK";
    case T_QUESTIONMARK:
    return "T_QUESTIONMARK";
    case T_EXP:
    return "T_EXP";
    case T_COMMA:
    return "T_COMMA";
    case T_PIPE:
    return "T_PIPE";
    case T_CIRCUMFLEX:
    return "T_CIRCUMFLEX";
    case T_DOUBLE_LESS_THAN:
    return "T_DOUBLE_LESS_THAN";
    case T_DOUBLE_GREATER_THAN:
    return "T_DOUBLE_GREATER_THAN";
    case T_SLASH:
    return "T_SLASH";
    case T_PERCENT:
    return "T_PERCENT";
    case T_MINUS:
    return "T_MINUS";
    case T_PLUS:
    return "T_PLUS";
    case T_EXCLAMATION_MARK:
    return "T_EXCLAMATION_MARK";
    case T_TILDE:
    return "T_TILDE";
    case T_ASTERIX:
    return "T_ASTERIX";
    case T_AMPERSAND:
    return "T_AMPERSAND";
    case T_L_C_BRACKET:
    return "T_L_C_BRACKET";
    case T_R_C_BRACKET:
    return "T_R_C_BRACKET";
    case T_L_S_BRACKET:
    return "T_L_S_BRACKET";
    case T_R_S_BRACKET:
    return "T_R_S_BRACKET";
    case T_L_R_BRACKET:
    return "T_L_R_BRACKET";
    case T_R_R_BRACKET:
    return "T_R_R_BRACKET";
    case T_DOT:
    return "T_DOT";
    case T_ARROW:
    return "T_ARROW";
    case T_DOUBLE_COLON:
    return "T_DOUBLE_COLON";
    case T_POINTER_TYPE:
    return "T_POINTER_TYPE";
    case T_VOID:
    return "T_VOID";
    case T_ID:
    return "T_ID";
    case T_PUSH:
    return "T_PUSH";
    case T_MOV:
    return "T_MOV";
    case T_ADD:
    return "T_ADD";
    case EXP:
    return "EXP";
    case T_LESS_THAN:
    return "T_LESS_THAN";
    case T_GREATER_THAN:
    return "T_GREATER_THAN";
    default:
    return "UNDEFINED";
  }
}
