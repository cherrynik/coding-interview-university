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
- **NOT FINISHED YET:** `insert(int before_what_index, int element)`
  - _No description yet._
- **NOT FINISHED YET:** `prepend(int element)`
  - _No description yet._

### Delete
- `pop()`
  - Removes the last element from container
    and returns its value.
- **NOT FINISHED YET:** `remove(int index)`
  - _No description yet._
- **NOT FINISHED YET:** `delete(int all_the_same_elements)`
  - _No description yet._
