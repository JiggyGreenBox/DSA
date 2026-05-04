#include <iostream>
#include <unordered_map>

using namespace std;

string header(30, '=');

void print_stats(unordered_map<int, int>& mpp){
    cout << header << endl;
    cout << mpp.bucket_count() << endl;
    cout << mpp.load_factor() << endl;
    cout << mpp.max_load_factor() << endl;
    cout << header << endl;
}

int main() {

    // Why you see 1 → 13 → 29 → 59 …
    // libstdc++ (GCC, Linux):
    //      Starts with 1 bucket (yep, weird but true).
    //      Then when it rehashes, instead of just doubling, it picks the next prime number from an internal list (13, 29, 59, 113, …).
    //      This is to spread hashes better and reduce collisions.
    // MSVC (Windows, Visual Studio):
    //      Starts with 8.
    //      Then grows roughly by powers of 2 (8 → 16 → 32 …).
    // libc++ (Clang, macOS):
    // Similar to MSVC, grows in powers of 2.

    unordered_map<int, int> mp;
    for (int i = 1; i <= 100; i++) {
        mp[i] = i;
        cout << "Size: " << mp.size()
             << " Buckets: " << mp.bucket_count()
             << " Load factor: " << mp.load_factor() << endl;
    }

    std::hash<int> hash_int;
    std::hash<std::string> hash_str;

    std::cout << "Hash of 42: " << hash_int(-1) << std::endl;
    std::cout << "Hash of 'hello': " << hash_str("hello") << std::endl;

    // hash of +ve number returns number back
    // template<>
    // struct hash<int> {
    //     size_t operator()(int x) const noexcept {
    //         return static_cast<size_t>(x);
    //     }
    // };

    
}