#include <iostream>
#include <vector>
#include "persistent_vector.h"

int main() {
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    persistent_vector<int> pv(v);
    persistent_vector<int> pv2 = pv.replace(6,700);
    pv.print_details();
    pv2.print_details();
    std::cout << "element 6 of pv is  " << pv[6] << std::endl;
    std::cout << "element 6 of pv2 is " << pv2[6] << std::endl;
    return 0;
}
