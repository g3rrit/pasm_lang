#pragma once

#include <cstddef>
#include <ostream>

struct id_token;
struct id_token_vec;
struct int_token;

namespace tree {

  struct type_def;

  struct type {

    virtual ~type() {}
    // size in bytes
    virtual std::size_t size() { return 0; }
    virtual friend std::ostream& operator<<(std::ostream&, const type&) { return os; }
  };

  struct unresolved_type : type {
    id_token_vec *id_vec;

    unresolved_type(id_token_vec*);
    ~unresolved_type();

    friend std::ostream& operator<<(std::ostream&, const unresolved_type&);
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

    friend std::ostream& operator<<(std::ostream&, const primative_type&);
  };

  struct pointer_type : type {
    type *t;

    pointer_type(type*);
    ~pointer_type();

    std::size_t size();

    friend std::ostream& operator<<(std::ostream&, const pointer_type&);
  };

  struct array_type : type {
    type *t;
    int_token *len;

    array_type(type*, int_token*);
    ~array_type();

    std::size_t size();

    friend std::ostream& operator<<(std::ostream&, const array_type&);
  };

  struct compound_type : type {
    type_def *t_def;

    compound_type(type_def*);
    ~compound_type();

    std::size_t size();

    friend std::ostream& operator<<(std::ostream&, const compound_type&);
  };
}
