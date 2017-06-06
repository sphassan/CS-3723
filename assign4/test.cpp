using namespace std;

#include <iostream>
#include <vector>
#include "persistent_vector.h"

int main() {
    std::vector<int> v { 10, 11, 12, 13, 15, 16, 17, 18 };
    persistent_vector<int> pv(v);
    for(int element : pv) {
        std::cout << element << std::endl;
    }
    return 0;
}
