#include <iostream>
#include <vector>
#include "persistent_vector.h"

int main() {
    std::vector<int> v { 0, 1, 2, 3, 4, 5, 6};
    persistent_vector<int> pv(v);
    pv.print_details();
    std::cout << "element at index 3 is " << pv[0] << std::endl;
    return 0;
}
