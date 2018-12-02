#pragma once

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

    token() : type(OTHER) {}

    token(int _type) : type(_type), vt(val_type::NONE_VAL) {}

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

    std::string get_str() const;

    friend std::ostream& operator<<(std::ostream &out, const token &token) {
        out << "token type: " << get_str(token) << " val_type: ";
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
