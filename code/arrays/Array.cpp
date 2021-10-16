#include "Array.h"

Array::Array(int input_size) : size_(0) {
  if (input_size < 1) {
    throw std::invalid_argument("Size of array cannot be less than 1.");
  }
                                                                       
  capacity_     = Array::CalculateSpaceAmortized(input_size);
  allocated_at_ = (value_type_*) malloc(capacity_);
}

inline size_t Array::CalculateSpaceAmortized(int size) const {
  return (size < min_size_) ?
    min_size_ :
    std::pow(2, ceil(log2(size)));
}
