# [DS] Array - Task 1
<!-- Made on C++11 -->

## Compile
```bash
g++ Array.cpp TestArray.cpp main.cpp
```

## Run
```bash
./a.out
```

## Functionality
### Read
- `is_empty()`
- `size()`
  - Returns how many items are hold.
- `capacity()`
  - Returns how many items can be hold.
- `find(int element)`
  - Returns first index of the found element.
    If there is no such an element, returns `-1`.

### Write
- `push_back(int element)`
  - Adds an element at the end of container.
- `insert(int before_what_index, int element)`
  - Adds an element on any available position at `[0, size)`,
    moving `container[before_what_index]` and all the elements after that right
- `push_front(int element)`
  - Adds an element at the beginning of container,
    moving `container[0]` and all the elements after that right

### Delete
- `pop()`
  - Removes the last element from container
    and returns its value.
- `remove_at(int index)`
  - Removes the element from `container[index]`
    and returns its value.
- `remove_all(int value)`
  - Removes all the elements
    with the same value of `value`.
