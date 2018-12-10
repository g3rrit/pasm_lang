#pragma once

#include <vector>

#include "mnemonic.h"

namespace tree {

  struct var_def;
  struct operand;

  struct statement {
    virtual ~statement() {}
  };

  struct var_def_statement : statement {
    var_def *var;

    var_def_statement(var_def*);
    ~var_def_statement();
  };

  struct mnemonic_statement : statement {
    mnemonic mem;
    mnemonic_statement(mnemonic);
    virtual ~mnemonic_statement() {}
  };

  struct u_mnemonic_statement : mnemonic_statement {
    operand *op;
    u_mnemonic_statement(mnemonic, operand*);
    ~u_mnemonic_statement();
  };

  struct d_mnemonic_statement : mnemonic_statement {
    operand *first;
    operand *second;
    d_mnemonic_statement(mnemonic, operand*, operand*);
    ~d_mnemonic_statement();
  };

  struct block_statement : std::vector<statement*> {
    ~block_statement();
  };
}
