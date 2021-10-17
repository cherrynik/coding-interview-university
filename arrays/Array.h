#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

class Array {
private:
  using value_type_ = int;
  const size_t type_size_ = sizeof(value_type_);
  const size_t min_size_ = 4 * type_size_;

  value_type_* allocated_at_;
  size_t capacity_,
	 size_;
  inline size_t CalculateSpaceAmortized(int size) const;

public:
  Array(int size = 16);

  ~Array();

  size_t capacity() const;
  size_t size() const;
  bool is_empty() const;
};
