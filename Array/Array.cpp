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
  return (size <= min_size_) ?
    min_size_ :
    std::pow(2, ceil(log2(size)));
}

void Array::resize_amortizely_when(Array::Operation operation) {
  bool has_to_realloc = false;

  switch (operation) {
    case Array::Operation::WRITE: {
      has_to_realloc = true;
      if (size_ == capacity_) {
        capacity_ *= 2;
      }
      break;
    }
    case Array::Operation::DELETE: {
      has_to_realloc = true;
      if (size_ <= capacity_ / 4 &&
          min_size_ <= capacity_ / 2) {
        capacity_ /= 2;
      }
      break;
    }
  }

  if (has_to_realloc) {
    allocated_at_ = (value_type*) realloc(allocated_at_, capacity_ * sizeof(value_type));
  }
}

void Array::save_and_move_when(Array::Operation operation,
                               value_type input,
			       int start_from_i) {
  if (start_from_i > size_ ||
      start_from_i < 0) {
    throw std::invalid_argument("Operation can't be executed: index is out of boundaries.");
  }

  switch (operation) {
    case Array::Operation::WRITE: {
      value_type current_val = input,
                 tmp;
      for (; start_from_i < size_; ++start_from_i) {
        tmp = *at_memory(start_from_i);
	*at_memory(start_from_i) = current_val;
	current_val = tmp;
      }

      Array::push_back(current_val);
      break;
    }

    case Array::Operation::DELETE: {
      for (; start_from_i < size_ - 1; ++start_from_i) {
	*at_memory(start_from_i) = *at_memory(start_from_i + 1);
      }

      Array::pop();
      break;
    }
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

void Array::push_back(value_type el) {
  *at_memory(size_) = el;
  ++size_;

  Array::resize_amortizely_when(Array::Operation::WRITE);
}

void Array::insert(int before_what_i, value_type el) {
  Array::save_and_move_when(Array::Operation::WRITE, el, before_what_i);
}

void Array::push_front(value_type el) {
  Array::insert(0, el);
}

Array::value_type Array::pop() {
  if (size_ == 0) {
    throw std::runtime_error("Array is already out of elements.");
  }

  value_type* last_el = at_memory(size_ - 1);
  value_type copy_of_last = *last_el;
  last_el = NULL;
  --size_;

  Array::resize_amortizely_when(Array::Operation::DELETE);

  return copy_of_last;
}

Array::value_type Array::remove_at(int i) {
  value_type copy_of_el = at(i);

  save_and_move_when(Array::Operation::DELETE, value_type(), i);

  return copy_of_el;
}

void Array::remove_all(value_type el) {
  int found_at = Array::find(el);

  while (found_at != -1) {
    Array::remove_at(found_at);
    found_at = Array::find(el);
  }
}

Array::value_type* Array::at_memory(int i) const {
  return allocated_at_ + i;
}

Array::value_type Array::at(int i) const {
  if (i < 0 || i >= size_) {
    throw std::invalid_argument("Index is out of boundaries.");
  }

  return *Array::at_memory(i);
}

Array::value_type Array::operator[](int i) const {
  return Array::at(i);
}

int Array::find(value_type requested_val) const {
  for (int i = 0; i < size_; ++i) {
    value_type current = *at_memory(i);
    if (current == requested_val) {
      return i;
    }
  }

  return -1;
}
