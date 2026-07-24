// #include <iostream>
// #include <vector>


// void print(int v) {
//     std::cout << v << std::endl;
// }

// void print(const std::vector<int> &v) {
//     std::cout << "[ ";
//     for(auto x : v) std::cout << x << " ";
//     std::cout << "]\n";
// };

// void print(const std::vector<std::vector<int>> &vec) {
//     std::cout << "[ ";
//     for(auto &v : vec) {
//         std::cout << "[ ";
//         for(auto x : v) std::cout << x << " ";
//         std::cout << "] ";
//     }    
//     std::cout << "]\n";
// };

// ============================
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

template<typename T>
void p(const T& x) {
    std::cout << x;
}

template<typename T>
void p(const std::vector<T>& v) {
    std::cout << "[ ";
    for (const auto& x : v) {
        p(x);
        std::cout << " ";
    }
    std::cout << "]";
}

template<typename T>
void print(const T& x) {
    p(x);
    std::cout << '\n';
}

// Allows:
// print({1,2,3});
// print({"a","b","c"});
template<typename T>
void print(std::initializer_list<T> list) {
    p(std::vector<T>(list));
    std::cout << '\n';
}

// Allows:
// print({{1,2},{3,4}});
// print({{"a","b"},{"c","d"}});
template<typename T>
void print(std::initializer_list<std::initializer_list<T>> list) {
    std::vector<std::vector<T>> v;

    for (const auto& row : list)
        v.emplace_back(row);

    p(v);
    std::cout << '\n';
}