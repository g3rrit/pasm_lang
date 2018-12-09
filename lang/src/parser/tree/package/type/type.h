#pragma once

#include <cstddef>

struct id_token;

namespace tree {

  struct type_def;

  struct type {

    virtual ~type();
    // size in bytes
    virtual std::size_t size();
  };

  struct unresolved_type : type {
    id_token *id;

    unresolved_type(id_token*);
  };

  struct primative_type : type {
    enum {
      I8,
      I16,
      I32,
      I64,
      U8,
      U16,
      U32,
      U64,
      F32,
      F64
    } type;
  };

  struct pointer_type : type {
    type *t;

    pointer_type(type*);

    std::size_t size();
  };

  struct array_type : type {
    type *t;
    std::size_t len;

    array_type(type*, std::size_t);
    ~array_type();

    std::size_t size();
  };

  struct compound_type : type {
    type_def *t_def;

    compound_type(type_def*);
  };
}
