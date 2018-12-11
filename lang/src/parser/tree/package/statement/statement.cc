#include "statement.h"

#include "mnemonic.h"

#include "token.h"
#include "var_def.h"
#include "operand.h"

namespace tree {

  label_statement::label_statement(id_token *_id)
    : id(_id) {}

  label_statement::~label_statement() {
    delete id;
  }

  mnemonic_statement::mnemonic_statement(mnemonic _mem, operand *_first, operand *_second)
    : mem(_mem), first(_first), second(_second) {}

  mnemonic_statement::~mnemonic_statement() {
    delete first;
    delete second;
  }

}
