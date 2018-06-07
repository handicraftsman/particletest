#include "particletest.hpp"

#include <iostream>
#include <typeinfo>

#include <cxxabi.h>

particletest::particletest(std::string _name)
: name(_name)
, ptest_amt(0)
, ptest_amt_all(0)
{}
particletest::~particletest() {}

int particletest::ptest_execute() {
  std::clog << "Test " << name << std::endl;
  
  int all_ok = true;
  for (std::pair<std::string, particletest::test_func> p : ptest_funcs) {
    std::clog << p.first << ": ";
    try {
      bool ok = p.second();
      std::clog << (ok ? "ok" : "fail");
      if (!ok) {
        all_ok = false;
      } else {
        ++ptest_amt;
      }
    } catch (std::exception& e) {
      int status;
      char* i = abi::__cxa_demangle(typeid(e).name(), 0, 0, &status);
      std::clog << "error" << std::endl;
      std::clog << "Exception: " << i << " - " << e.what();
      all_ok = false;
    }
    std::clog << std::endl;
  }
  std::clog << "Ok: " << ptest_amt << "/" << ptest_funcs.size() << std::endl;
  if (!all_ok) {
    for (std::string msg : ptest_log) {
      std::clog << "> " << msg << std::endl;
    }
  }
  std::clog << std::endl;
  return all_ok;
}

bool particletest::run_all(std::vector<particletest> tests) {
  bool all_ok = true;

  int amt_ok = 0;
  int amt_all = 0;

  for (auto test : tests) {
    all_ok = all_ok && test.ptest_execute();
    amt_all += test.ptest_amt_all;
    amt_ok += test.ptest_amt;
  }

  std::clog << "Total: " << amt_ok << "/" << amt_all << std::endl;

  return all_ok;
}

void particletest::ptest_register_test_(std::string name, particletest::test_func func) {
  ptest_funcs[name] = func;
  ++ptest_amt_all;
}

void particletest::ptest_push_to_log(std::string msg) {
  ptest_log.push_back(msg);
}