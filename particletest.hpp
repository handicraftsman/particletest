#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#define ptest_expect(st) \
  if (!(st)) { \
    ptest_push_to_log("Assertion failed: " #st); \
    return false; \
  }

#define ptest_register_test(name, func) ( \
  ptest_register_test_( \
    (name), \
    static_cast<particletest::test_func>( \
      std::bind( \
        (func), \
        this \
      ) \
    ) \
  ) \
)

class particletest {
public:
  typedef std::function<bool()> test_func;

  particletest(std::string name = "unnamed test");
  virtual ~particletest();

  int ptest_execute();

  static bool run_all(std::vector<particletest> tests);

protected:
  void ptest_register_test_(std::string name, test_func func);
  void ptest_push_to_log(std::string msg);

  std::string name;
  int ptest_amt;
  int ptest_amt_all;

private:
  std::map<std::string, test_func> ptest_funcs;
  std::vector<std::string> ptest_log;
};