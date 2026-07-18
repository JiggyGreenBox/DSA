#include <iostream>
#include <vector>

void print(const std::vector<int> &v) {
    std::cout << "[ ";
    for(auto x : v) std::cout << x << " ";
    std::cout << "]\n";
};

void print(const std::vector<std::vector<int>> &vec) {
    std::cout << "[ ";
    for(auto &v : vec) {
        std::cout << "[ ";
        for(auto x : v) std::cout << x << " ";
        std::cout << "] ";
    }    
    std::cout << "]\n";
};