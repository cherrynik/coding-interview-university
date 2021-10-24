#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

class Array {
private:
  using value_type = std::string;

  const uint8_t min_size_ = 16;

  enum class Operation {
    READ,
    WRITE,
    DELETE
  };

  value_type* allocated_at_;
  size_t capacity_,
	 size_;
  size_t calc_nearest_step2(int size) const;
  void resize_amortizely_when(Operation operation);
  void save_and_move_when(Array::Operation operation,
                          value_type input,
                          int start_from_i);
  value_type* at_memory(int i) const;

public:
  Array(int size = 1);

  ~Array();

  void push_front(value_type el);
  void insert(int before_what_index, value_type el);
  void push_back(value_type el);

  value_type pop();
  value_type remove_at(int index);
  void remove_all(value_type el);

  size_t capacity() const;
  size_t size() const;
  bool is_empty() const;

  value_type at(int i) const;
  value_type operator[](int i) const;
  int find(value_type requsted_val) const;
};
