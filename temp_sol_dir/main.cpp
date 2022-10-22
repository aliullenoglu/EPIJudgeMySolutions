#include <iostream>
#include <vector>
using namespace std;


void print_vector(const vector<int>& v) {

    if (v.size() == 0) {
        cout << "empty vector" << endl;
        return; 
    }

    for (auto x : v) {
        cout << x << " ";
    }
    cout << endl;
}

void DutchFlagPartitionWithCounts(int pivot_index, vector<int>* A_ptr) {
    
    int white {0}, grey {0}, black {0};
    
    for (auto a : *A_ptr) {
        if (a == 1) {
            white++;
        } else if (a == 2) {
            grey++;
        } else if (a == 3) {
            black++;
        }
    }

    int i = 0;
    for (; i < white; i++) {
        (*A_ptr)[i] = 1;
    }
    for (; i < grey+white; i++) {
        (*A_ptr)[i] = 2;
    }
    for (; i < black+white+grey; i++) {
        (*A_ptr)[i] = 3;
    }

    cout << white << "-" << grey << "-" << black << endl;

    return;
}

void DutchFlagPartition(int pivot_index, vector<int>* A_ptr) {
    
    if (A_ptr == nullptr || A_ptr->size() == 0) {
        return;
    }

    int pivot = (*A_ptr)[pivot_index];
    
    cout << pivot << endl;

    int j, k = 0;
    for (int i = 0; i < A_ptr->size(); i++) {
        
        j = i;
        if ((*A_ptr)[j] <= pivot) {
            while((*A_ptr)[j] != (*A_ptr)[j-1] && j > 0 ) {
                swap( (*A_ptr)[j], (*A_ptr)[j-1] );
                cout << "swapping " << (*A_ptr)[j] << " with " << (*A_ptr)[j-1] << endl;
                j--;
            }
        }
    }

    return;
}


int main() {
    vector<int> v1 {2,3,1,3,2,1,3,1,2,3,1,2};
    vector<int> v2 {2,1,3};
    vector<int> v3;
    vector<int> v4 {3,1};

    DutchFlagPartition(0, &v1);
    DutchFlagPartition(0, &v2);
    DutchFlagPartition(1, &v3);
    DutchFlagPartition(1, &v4);

    print_vector(v1);
    print_vector(v2);
    print_vector(v3);
    print_vector(v4);

    return 0;
}
