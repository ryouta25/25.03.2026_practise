#include "pe-vector.hpp"
using knk::Vector

bool test1(const char ** pname)
{
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}

bool test2(const char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { test1,"Vector must be default" },
    { test2, "Vector must be empty" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(test_t);
  size_t failed = 0;
  for(size_t i = 0; i < count; ++i) {
    bool r = tests[i](&testName);
    if (!r) {
      ++failed;
      std::cout << "Failed: " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
