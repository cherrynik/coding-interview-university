#include "TestArray.h"
#include "TestLib.h"

#include "Array.h"

#include <climits>

void TestArray() {
  RUN_TEST(TestInitializationAccess);
  RUN_TEST(TestPush);
  RUN_TEST(TestRead);
  RUN_TEST(TestPop);
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
    ASSERT_EQUAL(container.capacity() - 1, INT_MAX); // Because capacity is the type of size_t.
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

    container.push(first);
    container.push(second);

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
      container.push(i);
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
      container.push(i);
    }

    ASSERT_EQUAL(container[0], 0);
    ASSERT_EQUAL(container.at(size - 1), size - 1);
  }
}

void TestPop() {
  {

  }
}
