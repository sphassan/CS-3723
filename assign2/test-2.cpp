#include <iostream>
#include <vector>
#include "persistent_vector.h"

int main() {
    std::vector<int> v { 10, 20 };
    persistent_vector<int> pv(v);
    for(size_t i=0; i<v.size(); i++) {
        if ( pv[i] != v[i] ) {
            std::cerr << "test-2: FAILED equality check at index " << i << std::endl;
            return -1;
        }
    }
    try {
       pv[v.size()]; 
       std::cerr << "test-2: FAILED to throw exception" << std::endl;
       return -1; // this should fail
    } catch (std::out_of_range ex) {
       std::cout << "test-2: PASS " << std::endl;
       return 0;
    } catch (...) {
       std::cerr << "test-2: FAILED to throw std::out_of_range exception" << std::endl;
       return -1; 
    }
}
