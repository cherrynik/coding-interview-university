#include "TestArray.h"
#include "TestLib.h"

#include "Array.h"

#include <climits>

void TestArray() {
  RUN_TEST(TestInitializationAccess);
  RUN_TEST(TestPush);
  RUN_TEST(TestRead);
  RUN_TEST(TestPop);
  RUN_TEST(TestAmortizedResizing);
  RUN_TEST(TestFind);
  RUN_TEST(TestPushFront);
  RUN_TEST(TestInsert);
}

void TestInitializationAccess() {
  {
    const Array container{};
    ASSERT_EQUAL(container.capacity(), 16);
    ASSERT_EQUAL(container.size(), 0);
    ASSERT(container.is_empty());
  }

  {
    const Array container(8);
    ASSERT_EQUAL(container.capacity(), 16);
    ASSERT_EQUAL(container.size(), 0);
    ASSERT(container.is_empty());
  }

  {
    const Array container(17);
    ASSERT_EQUAL(container.capacity(), 32);
  }

  {
    const Array container(32);
    ASSERT_EQUAL(container.capacity(), 32);
  }

  {
    const Array container(INT_MAX);
    ASSERT(container.capacity() > 0);
    ASSERT(container.is_empty());
    ASSERT_EQUAL(container.capacity() - 1, INT_MAX); // Because capacity is of the type of size_t.
    ASSERT_EQUAL(container.size(), 0);
  }

  {
    try {
      const Array container(0);
      ASSERT_HINT(container.size(), "Container has to be non-alive.");
    } catch (const std::exception& e) {} 
  }

  {
    try {
      const Array container(-1);
      ASSERT_HINT(container.size(), "Container has to be non-alive.");
    } catch (const std::exception& e) {}
  }

  {
    try {
      const Array container(INT_MIN);
      ASSERT_HINT(container.size(), "Container has to be non-alive.");
    } catch (const std::exception& e) {}
  }
}

void TestPush() {
  {
    Array container(2);
    int first = 100500,
	second = -15000;

    container.push_back(first);
    container.push_back(second);

    ASSERT_EQUAL(container[0], first);
    ASSERT_EQUAL(container.at(1), second);
    ASSERT_EQUAL(container.size(), 2);
    ASSERT_EQUAL(container.capacity(), 16);
  }
}

void TestRead() {
  int size = 16;

  {
    Array container(size);
    for (int i = 0; i < size; ++i) {
      container.push_back(i);
    }

    try {
      ASSERT_HINT(container.at(-1), "Index of element has to be non-reached.");
    } catch (const std::exception& e) {}

    try {
      ASSERT_HINT(container[size], "Index of element has to be non-reached.");
    } catch (const std::exception& e) {}
  }

  {
    Array container(size);
    for (int i = 0; i < size; ++i) {
      container.push_back(i);
    }

    ASSERT_EQUAL(container[0], 0);
    ASSERT_EQUAL(container.at(size - 1), size - 1);
  }
}

void TestPop() {
  {
    int size = 16;
    Array container;

    for (int i = 0; i < size; ++i) {
      container.push_back(i);
    }

    for (int i = size; i > 0; --i) {
      ASSERT_EQUAL(container.pop(), i - 1);
    }
  }

  {
    Array container;

    try {
      ASSERT_HINT(container.pop(), "There is no last element in array to pop.");
    } catch (const std::exception& e) {}
  }
}

void TestAmortizedResizing() {
  {
    int min_size = 16;
    Array container(min_size);
    
    for (int i = 0; i < min_size; ++i) {
      container.push_back(i);
    }
    ASSERT_EQUAL(container.capacity(), min_size * 2);

    for (int i = min_size; i > min_size / 2; --i) {
      container.pop();
    }
    ASSERT_EQUAL(container.capacity(), min_size);

    for (int i = min_size / 2; i > 0; --i) {
      container.pop();
    }
    ASSERT_EQUAL(container.capacity(), min_size);
    ASSERT_EQUAL(container.size(), 0);
  }

  {
    int size = 1024;
    Array container, container2;

    for (int i = 1; i <= size; ++i) {
      container.push_back(i);
      container2.push_back(i * 2);
    }
    
    // Checking if elements aren't overwritten after memory reallocation
    ASSERT_EQUAL(container[3], 4);
    ASSERT_EQUAL(container2[0], 2);
    ASSERT_EQUAL(container.size(), size);
    ASSERT_EQUAL(container.capacity(), size * 2);
  }
}

void TestFind() {
  {
    Array container;
    int size = 16;

    for (int i = 1; i <= size; ++i) {
      container.push_back(i);
    }

    ASSERT_EQUAL(container.find(3), 2);
    ASSERT_EQUAL(container.find(0), -1);
  }
}

void TestPushFront() {
  {
    Array container;
    int size = 8;

    for (int i = 0; i < size; ++i) {
      container.push_front(i);
    }

    container.push_front(20);
    container.push_front(10);

    ASSERT_EQUAL(container[0], 10);
    ASSERT_EQUAL(container.at(1), 20);
    ASSERT_EQUAL(container[container.size() - 1], 0);
    ASSERT_EQUAL(container.at(2), size - 1);
    ASSERT_EQUAL(container.capacity(), 16);
    ASSERT_EQUAL(container.size(), 10);
  }
}

void TestInsert() {
  {
    Array container;
    int size = 5;

    for (int i = 0; i < size; ++i) {
      container.push_back(i);
    }

    container.insert(0, 333);
    container.insert(3, 5423);
    
    ASSERT_EQUAL(container[0], 333);
    ASSERT_EQUAL(container[1], 0);
    ASSERT_EQUAL(container[2], 1);
    ASSERT_EQUAL(container[3], 5423);
    ASSERT_EQUAL(container[4], 2);
    ASSERT_EQUAL(container.size(), 7);
    ASSERT_EQUAL(container.capacity(), 16);
  }

  {
    Array container;

    container.insert(0, 6);

    try {
      container.insert(-1, 3);
      ASSERT_EQUAL_HINT(container.size(), 1, "Insert hasn't to run as it couldn't operate with unavailable indices.");
    } catch (const std::exception& e) {}

    try {
      container.insert(2, 0);
      ASSERT_EQUAL_HINT(container.size(), 1, "Insert hasn't to run as it couldn't operate with unavailable indices.");
    } catch (const std::exception& e) {}
  }
}
