#include "TestArray.h"
#include "TestLib.h"

#include "Array.h"

void TestArray() {
  RUN_TEST(TestInitialization);
}

void TestInitialization() {
  const Array container;
  ASSERT_EQUAL(container.capacity(), 16);
}
