#include <iostream>
#include <vector>
#include <string>
#include "persistent_vector.h"

int main() {
    std::vector<std::string> v { "10", "11", "12", "13" };
    persistent_vector<std::string> pv(v);
    for(size_t i=0; i<v.size(); i++) {
        if ( pv[i] != v[i] ) {
            std::cerr << "test-str: FAILED equality check at index " << i << std::endl;
            return -1;
        }
    }
    try {
       pv[v.size()]; 
       std::cerr << "test-str: FAILED to throw exception" << std::endl;
       return -1; // this should fail
    } catch (std::out_of_range ex) {
       std::cout << "test-str: PASS " << std::endl;
       return 0;
    } catch (...) {
       std::cerr << "test-str: FAILED to throw std::out_of_range exception" << std::endl;
       return -1; 
    }
}
