#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double current_min = std::numeric_limits<double>::max();
  double max_profit = 0.0;

  for (auto p : prices) {
    if (p < current_min) {
      current_min = p;
    } else {
      max_profit = std::max(max_profit, p - current_min);
    }
  }

  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
