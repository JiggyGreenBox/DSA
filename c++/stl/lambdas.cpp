#include <iostream>
#include <vector>

using namespace std;
#include <functional> // Needed for std::function

/*
    [capture] (parameters) { code };

*/

void accept_lamdba(function<void()> func){
    func();
    func();
}

int main() {

    //================================================================
    // 1. no capture or parameters
    auto message = [](){
        cout << "Hello" << endl;
    };

    message();

    //================================================================
    // 2. parameters
    auto add = [](int a, int b){
        return a + b; 
    };

    cout << add(3,5) << endl;

    //================================================================
    // 3. pass lambda to a function    
    accept_lamdba(message);


    //================================================================
    // 4. capture
    //      by val
    int x = 10;
    auto show1 = [x](){  
        // x+=5; //not possible 
        cout << x << endl;
    };
    show1();

    //      by ref
    auto show2 = [&x](){  
        x+=5; //not possible 
        cout << x << endl;
    };
    show2();
    cout << x << endl; // 15

    return 0;
}