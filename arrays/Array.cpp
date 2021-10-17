#include "Array.h"

Array::Array(int input_size) : size_(0), min_size_(16) {
  if (input_size < 1) {
    throw std::invalid_argument("Size of array cannot be less than 1.");
  }
                                                                       
  capacity_     = Array::CalculateSpaceAmortized(input_size);
  allocated_at_ = (value_type*) malloc(capacity_);
}

Array::~Array() {
  free(allocated_at_);
}

inline size_t Array::CalculateSpaceAmortized(int size) const {
  return (size < min_size_) ?
    min_size_ :
    std::pow(2, ceil(log2(size)));
}

size_t Array::capacity() const {
  return capacity_;
}


size_t Array::size() const {
  return size_;
}

bool Array::is_empty() const {
  return size_ == 0;
}

void Array::push(value_type el) {
  *(allocated_at_ + size_) = el;
  ++size_;
  // std::cout << *(allocated_at_ + size_) << std::endl;
}

Array::value_type Array::at(int index) const {
  return *(allocated_at_ + index);
}

Array::value_type Array::operator[](int index) const {
  return Array::at(index);
}
