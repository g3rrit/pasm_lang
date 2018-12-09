#pragma once

#include "token_types.h"

#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <vector>

struct primary_token {
  int type;
  primary_token(int _type);
};

struct id_token : primary_token {
  char *val;
  id_token(char *_val);
  ~id_token();
  bool operator<(const id_token&) const;
  bool operator>(const id_token&) const;
};

struct id_token_vec : std::vector<id_token> {
  bool operator<(const id_token_vec&) const;
};

struct float_token : primary_token {
  float val;
  float_token(float _val);
};

struct string_token : primary_token {
  char *val;
  string_token(char *_val);
  ~string_token();
};

struct int_token : primary_token {
  int val;
  int_token(int _val);
};

struct token {
    int type;

    enum val_type {
        STR_VAL,
        INT_VAL,
        FLOAT_VAL,
        NONE_VAL
    } vt;

    union {
      char *str_val;
      int int_val;
      double float_val;
    };

    token();

    token(int _type);

#define check_val_type()              \
  if(vt == val_type::STR_VAL) { \
    free(str_val);                    \
  }

    ~token()  {
      check_val_type();
    }

    inline void set_str_val(char *val) {
      check_val_type();
      str_val = (char*) malloc(strlen(val) + 1);
      strcpy(str_val, val);
      vt = val_type::STR_VAL;
    }

    inline void set_int_val(int val) {
      check_val_type();
      int_val = val;
      vt = val_type::INT_VAL;
    }

    inline void set_float_val(double val) {
      check_val_type();
      float_val = val;
      vt = val_type::FLOAT_VAL;
    }

    /* OVERLOADED CASTS */

    operator id_token();
    operator float_token();
    operator int_token();
    operator string_token();

    /* STRING CONVERSION */

    std::string get_str() const;

    friend std::ostream& operator<<(std::ostream &out, const token &token) {
        out << "token type: " << token.get_str() << " val_type: ";
        switch(token.vt) {
          case val_type::NONE_VAL:
            out << "NONE ";
            break;
          case val_type::STR_VAL:
            out << "STR_VAL: " << token.str_val;
            break;
          case val_type::FLOAT_VAL:
            out << "FLOAT_VAL: " << token.float_val;
            break;
          case val_type::INT_VAL:
            out << "INT_VAL: " << token.int_val;
            break;
        }
        out << std::endl;
        return out;
    }
};
