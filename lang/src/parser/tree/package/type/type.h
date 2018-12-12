#pragma once

#include <cstddef>

struct id_token;
struct int_token;

namespace tree {

  struct type_def;

  struct type {

    virtual ~type() {}
    // size in bytes
    virtual std::size_t size() { return 0; }
  };

  struct unresolved_type : type {
    id_token *id;

    unresolved_type(id_token*);
    ~unresolved_type();
  };

  struct primative_type : type {
    enum p_type {
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
    } t;

    primative_type(p_type);
    ~primative_type();

    std::size_t size();
  };

  struct pointer_type : type {
    type *t;

    pointer_type(type*);
    ~pointer_type();

    std::size_t size();
  };

  struct array_type : type {
    type *t;
    int_token *len;

    array_type(type*, int_token*);
    ~array_type();

    std::size_t size();
  };

  struct compound_type : type {
    type_def *t_def;

    compound_type(type_def*);
    ~compound_type();

    std::size_t size();
  };
}
