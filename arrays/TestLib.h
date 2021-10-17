#pragma once
#include <iostream>

void PrintTestFailed(const std::string& hint,
                     const std::string& file,
		     unsigned int line,
		     const std::string& func_err,
		     const std::string& test_err,
		     const std::string& what_err) {
  std::cerr << file << "(" << line << "): " <<
               func_err << ": " <<
	       test_err <<
               "(" << what_err << ") failed.";
  if (not hint.empty()) {
    std::cerr << " Hint: " << hint;
  }
}

void AssertImpl(bool val,
                const std::string& hint,
	        const std::string& file,
	        unsigned int line,
	        const std::string& func_err,
	        const std::string& test_err,
	        const std::string& what_err) {
  if (not val) {
    PrintTestFailed(hint, file, line, func_err, test_err, what_err);
    abort();
  }
}

template<typename First, typename Second>
void AssertEqualImpl(const First& val1,
		     const Second& val2,
                     const std::string& hint,
	             const std::string& file,
	             unsigned int line,
	             const std::string& func_err,
	             const std::string& test_err,
	             const std::string& what_err) {
  if (val1 != val2) {
    PrintTestFailed(hint, file, line, func_err, test_err, what_err);
    abort();
  }
}

void RunTestImpl(void (*test_to_call)(), const std::string& test_name) {
  (*test_to_call)();
  std::cerr << test_name << " OK." << std::endl;
}

#define ASSERT(val) AssertImpl(not not(val), "", __FILE__, __LINE__, __FUNCTION__, "ASSERT", #val);
#define ASSERT_HINT(val, hint) AssertImpl(not not(val), #hint, __FILE__, __LINE__, __FUNCTION__, "ASSERT", #val);
#define ASSERT_EQUAL(val1, val2) AssertEqualImpl((val1), (val2), "", __FILE__, __LINE__, __FUNCTION__, "ASSERT", (std::string(#val1).append(" != ").append(#val2)));
#define ASSERT_EQUAL_HINT(val1, val2, hint) AssertEqualImpl((val1), (val2), #hint, __FILE__, __LINE__, __FUNCTION__, "ASSERT", (std::string(#val1).append(" != ").append(#val2)));
#define RUN_TEST(test) RunTestImpl(test, #test);
