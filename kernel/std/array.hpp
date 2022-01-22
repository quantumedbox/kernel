#pragma once

namespace KS
{

template<typename T, size_t n>
class Array
{
  T data[n];

public:
  Array() = default;
  Array(const Array&) = default;
  Array(Array&&) = default;
  ~Array() = default;

  Array& operator= (const Array &) = default;
  Array& operator= (Array &&) = default;

  T& operator[] (const size_t & index) { return Array::data[index]; }
  const T& operator[] (const size_t & index) const { return Array::data[index]; }

  T* begin() { return Array::data; }
  T* end() { return Array::data + n; }

  const T* cbegin() const { return Array::data; }
  const T* cend() const { return Array::data + n; }

  static constexpr size_t size() { return n; }
};

}
