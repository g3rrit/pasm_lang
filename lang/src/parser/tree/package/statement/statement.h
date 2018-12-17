#pragma once

#include <ostream>
#include <vector>

#include "mnemonic.h"

struct id_token;

namespace tree {

  struct var_def;
  struct operand;

  struct statement {
    virtual ~statement() {}

    virtual friend std::ostream& operator<<(std::ostream&, const statement&)
    { return os; }
  };

  struct label_statement : statement {
    id_token *id;
    label_statement(id_token*);
    ~label_statement();

    friend std::ostream& operator<<(std::ostream&, const label_statement&);
  };

  struct mnemonic_statement : statement {
    mnemonic mem;
    operand *first;
    operand *second;
    mnemonic_statement(mnemonic, operand*, operand*);
    ~mnemonic_statement();

    friend std::ostream& operator<<(std::ostream&, const mnemonic_statement&);
  };

}
