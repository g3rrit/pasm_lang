#include "statement.h"

#include "mnemonic.h"

#include "var_def.h"
#include "operand.h"

namespace tree {

  var_def_statement::var_def_statement(var_def *_var)
    : var(_var) {}

  var_def_statement::~var_def_statement() {
    delete var;
  }

  mnemonic_statement::mnemonic_statement(mnemonic _mem)
    : mem(_mem) {}

  u_mnemonic_statement::u_mnemonic_statement(mnemonic _mem, operand *_op)
    : mnemonic_statement(_mem), op(_op) {}

  u_mnemonic_statement::~u_mnemonic_statement() {
    delete op;
  }

  d_mnemonic_statement::d_mnemonic_statement(mnemonic _mem, operand *_first, operand *_second)
    : mnemonic_statement(_mem), first(_first), second(_second) {}

  d_mnemonic_statement::~d_mnemonic_statement() {
    delete first;
    delete second;
  }

  block_statement::~block_statement() {
    for(statement *s : *this) {
      delete s;
    }
  }

}
