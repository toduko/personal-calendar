#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include "Optional.hpp"

#include <cstddef>
#include <iostream>

template <typename T>
class Vector
{
private:
  static const size_t DEFAULT_CAPACITY = 4;
  Optional<T> *values;
  size_t size;
  size_t capacity;

  void free()
  {
    delete[] this->values;
  }

  void copy(Optional<T> *values, size_t size)
  {
    this->values = new Optional<T>[this->capacity];
    for (size_t i = 0; i < size; ++i)
    {
      this->push(values[i]);
    }
  }

  void swap(Optional<T> &val1, Optional<T> &val2)
  {
    Optional<T> temp = val1;
    val1 = val2;
    val2 = temp;
  }

public:
  Vector() : size(0), capacity(Vector::DEFAULT_CAPACITY)
  {
    this->values = new Optional<T>[Vector::DEFAULT_CAPACITY];
  }

  Vector(const Vector &other) : size(0), capacity(DEFAULT_CAPACITY)
  {
    this->copy(other.values, other.size);
  }

  Vector &operator=(const Vector &other)
  {
    if (this != &other)
    {
      this->free();
      this->size = 0;
      this->capacity = Vector::DEFAULT_CAPACITY;
      this->copy(other.values, other.size);
    }

    return *this;
  }

  ~Vector()
  {
    this->free();
  }

  void push(const Optional<T> &data)
  {
    this->values[this->size++] = data;

    if (this->size == this->capacity)
    {
      this->resize();
    }
  }

  void resize()
  {
    this->capacity *= 2;
    Optional<T> *newValues = new Optional<T>[this->capacity];

    for (size_t i = 0; i < this->size; ++i)
    {
      newValues[i] = this->values[i];
    }

    this->free();
    this->values = newValues;
  }

  T &operator[](size_t index)
  {
    if (index >= this->size)
    {
      throw "Invalid index";
    }
    return this->values[index].getData();
  }

  T operator[](size_t index) const
  {
    if (index >= this->size)
    {
      throw "Invalid index";
    }
    return this->values[index].getData();
  }

  size_t getSize() const
  {
    return this->size;
  }

  void sort()
  {
    for (size_t i = 0; i < this->size; ++i)
    {
      bool hasSwapped = false;

      for (size_t j = 0; j < this->size - i - 1; ++j)
      {
        if (this->values[j + 1] < this->values[j])
        {
          this->swap(this->values[j], this->values[j + 1]);
          hasSwapped = true;
        }
      }

      if (!hasSwapped)
      {
        break;
      }
    }
  }

  int find(const T &value)
  {
    for (size_t i = 0; i < this->size; ++i)
    {
      if (this->values[i] == value)
      {
        return i;
      }
    }

    return -1;
  }

  bool has(const T &value)
  {
    return this->find(value) != -1;
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &vector)
{
  for (size_t i = 0; i < vector.getSize(); ++i)
  {
    os << vector[i] << (i < vector.getSize() - 1 ? " " : "");
  }

  return os;
}

#endif