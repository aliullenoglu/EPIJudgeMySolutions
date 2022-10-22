#include "test_framework/generic_test.h"
using namespace std;

short Parity(unsigned long long x) {
  
  short parity = 0;

  while (x > 0) {
    x = x & (x - 1); // clear the lowest bit
    parity++;
  }

  return parity % 2;
}

int main(int argc, char* argv[]) {

  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
