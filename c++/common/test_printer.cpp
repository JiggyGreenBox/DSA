#include "printer.h"

int main() {

    
    print(10);

    print("hello");

    print(std::string("world"));

    print(std::vector<int>{1,2,3});

    print(std::vector<std::string>{"a","b","c"});

    print(std::vector<std::vector<int>>{{1,2},{3,4}});

    print({1,2,3});

    print({"one","two","three"});

    print({{1,2},{3,4}});

    print({{"a","b"},{"c","d"}});

    return 0;
}