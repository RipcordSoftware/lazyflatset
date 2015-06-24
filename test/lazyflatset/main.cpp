#include <iostream>
#include <chrono>

#include "../../lazyflatset.hpp"

int main() {
    
    const unsigned max = 30 * 1000 * 1000;
    
    rs::LazyFlatSet<unsigned> set(16, 32 * 1024);
    
    auto start = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < max; ++i) {
        set.insert(max - i - 1);
        //set.insert(i);
        
        if ((i & 0x7fff) == 0) {
            std::cout << i << std::endl;
        }
    }
    
    auto duration = std::chrono::steady_clock::now() - start;
    auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    
    std::cout << "Populate: " << durationMS.count() << "ms" << std::endl;
    
    std::cout << "Size: " << set.size() << std::endl;
    std::cout << "[0] = " << set[0] << std::endl;
    std::cout << "[1] = " << set[1] << std::endl;
    std::cout << "[10] = " << set[10] << std::endl;
    std::cout << "[1000] = " << set[1000] << std::endl;    

    return 0;
}

