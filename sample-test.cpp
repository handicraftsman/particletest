#include "particletest.hpp"

class sample_test : public particletest {
public:
  sample_test() {
    ptest_register_test("1 + 1 == 2", &sample_test::one_plus_one_is_two);
  }
  virtual ~sample_test() {}

  bool one_plus_one_is_two() {
    ptest_expect(1 + 1 == 2);

    return true;
  }
};

int main(int argc, char** argv) {
  return particletest::run_all({sample_test()});
}