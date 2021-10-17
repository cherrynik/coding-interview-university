#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

class Array {
private:
  using value_type = int;

  const size_t min_size_ = 16;

  value_type* allocated_at_;
  size_t capacity_,
	 size_;
  size_t CalculateSpaceAmortized(int size) const;

public:
  Array(int size = 16);

  ~Array();

  void prepend(value_type el);
  void push(value_type el);
  void insert(int beforeWhatIndex, value_type el);

  size_t capacity() const;
  size_t size() const;
  bool is_empty() const;

  value_type at(int index) const;
  value_type operator[](int index) const;
};
