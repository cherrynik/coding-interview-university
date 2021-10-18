#include "Array.h"

Array::Array(int input_size) : size_(0), min_size_(4 * sizeof(value_type)) {
  if (input_size < 1) {
    throw std::invalid_argument("Size of array cannot be less than 1.");
  }

  capacity_     = Array::calc_nearest_step2(input_size);
  allocated_at_ = (value_type*) malloc(capacity_ * sizeof(value_type));
}

Array::~Array() {
  free(allocated_at_);
}

size_t Array::calc_nearest_step2(int size) const {
  return (size < min_size_) ?
    min_size_ :
    std::pow(2, ceil(log2(size)));
}

void Array::resize_amortizely(Array::Operation operation) {
  bool hasToReloc = false;
  if (size_ == capacity_) {
    capacity_ *= 2;
    hasToReloc = true;
  } else if (min_size_ < (size_ <= (capacity_ / 4)) &&
             operation == Array::Operation::DELETE) {
    capacity_ /= 2;
    hasToReloc = true;
  }

  if (hasToReloc) {
    allocated_at_ = (value_type*) realloc(allocated_at_, capacity_ * sizeof(value_type));
  }
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

  Array::resize_amortizely(Array::Operation::WRITE);
}

Array::value_type Array::pop() {
  value_type* last_element = allocated_at_ + size_ - 1;
  value_type copy = *last_element;
  last_element = NULL;
  --size_;

  Array::resize_amortizely(Array::Operation::DELETE);

  return copy;
}

Array::value_type Array::at(int index) const {
  if (index < 0 || index >= size_) {
    throw std::invalid_argument("Index is out of boundaries.");
  }
  return *(allocated_at_ + index);
}

Array::value_type Array::operator[](int index) const {
  return Array::at(index);
}
