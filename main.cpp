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
  test_t tests[] = {
    test1,
    test2
  };
  constexpr size_t count = sizeof(tests) / sizeof(test_t);
  for(size_t i = 0; i < count; ++i) {
    bool r = tests[i](&testName);
    if (!r) {
      std::cout << "Failed: " << testName << "\n";
    }
  }
}
