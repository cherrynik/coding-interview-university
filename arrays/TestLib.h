#pragma once
#include <iostream>

void AssertImpl(bool val,
                const std::string& hint,
	        const std::string& file,
	        unsigned int line,
	        const std::string& func_err,
	        const std::string& test_err,
	        const std::string& what_err);

template<typename First, typename Second>
void AssertEqualImpl(const First& val1,
		     const Second& val2,
                     const std::string& hint,
	             const std::string& file,
	             unsigned int line,
	             const std::string& func_err,
	             const std::string& test_err,
	             const std::string& what_err);

void PrintTestFailed(const std::string& hint,
                     const std::string& file,
		     unsigned int line,
		     const std::string& func_err,
		     const std::string& test_err,
		     const std::string& what_err);

void RunTestImpl(void (*test_to_call)(), const std::string& test_name);

#define ASSERT(val) AssertImpl(not not(val), "", __FILE__, __LINE__, __FUNCTION__, "ASSERT", #val);
#define ASSERT_HINT(val, hint) AssertImpl(not not(val), #hint, __FILE__, __LINE__, __FUNCTION__, "ASSERT", #val);
#define ASSERT_EQUAL(val1, val2) AssertEqualImpl((val1), (val2), "", __FILE__, __LINE__, __FUNCTION__, "ASSERT", (std::string(#val1).append(" != ").append(#val2)));
#define ASSERT_EQUAL_HINT(val1, val2, hint) AssertEqualImpl((val1), (val2), #hint, __FILE__, __LINE__, __FUNCTION__, "ASSERT", (std::string(#val1).append(" != ").append(#val2)));
#define RUN_TEST(test) RunTestImpl(test, #test);
