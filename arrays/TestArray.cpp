#include "TestArray.h"
#include "TestLib.h"

#include "Array.h"

#include <climits>

void TestArray() {
  RUN_TEST(TestInitialization);
}

void TestInitialization() {
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
      ASSERT_HINT(container.size(), "Container has to be non-alive");
    } catch (const std::exception& e) {} 
  }
  {
    try {
      const Array container(-1);
      ASSERT_HINT(container.size(), "Container has to be non-alive");
    } catch (const std::exception& e) {}
  }
  {
    try {
      const Array container(INT_MIN);
      ASSERT_HINT(container.size(), "Container has to be non-alive");
    } catch (const std::exception& e) {}
  }
}
