#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using namespace std;

enum class Color { kRed, kWhite, kBlue };

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {

    if (A_ptr == nullptr || A_ptr->size() == 0) {
        return;
    }

    int pivot = static_cast<int>((*A_ptr)[pivot_index]);
 //   cout << pivot << endl;
    int j = 0;
    for (int i = 0; i < A_ptr->size(); i++) {
        
        j = i;
        if ( static_cast<int>((*A_ptr)[j]) <= pivot) {
            while((*A_ptr)[j] < (*A_ptr)[j-1] && j > 0 ) {
                swap( (*A_ptr)[j], (*A_ptr)[j-1] );
   //             cout << "swapping " << (int)(*A_ptr)[j] << " with " << (int)(*A_ptr)[j-1] << endl;
                j--;
            }
        }
    }

    return;
}
void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
