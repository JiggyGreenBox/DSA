# pointers
## void pointer
size is unsigned 32 bit or 64 bit integer
```cpp
void* x;
size_t y = (size_t) x; // ok (explicit conversion)
// size_t y = x;
// compile error (implicit conversion)
```


Dereferencing:
```cpp
int* ptr1   = new int;
*ptr1       =  4;     // dereferencing (assignment)
int a       = *ptr1;  // dereferencing (get value)

//  array
int* ptr2   = new int[10];
ptr2[2]     = 3;
int var     = ptr2[4];
```


Address-of operator and Reference Operator
```cpp
int  a  = 3;
int* b  = &a; // address of a is stored in pointer b

a++;
cout << *b; // 4

// do not confuse with a reference
T& var = ...
```

## wild pointer - A wild pointer is a pointer not initialized
```cpp
int* ptr; // wild pointer
```

## Pointer Arithmetic

`ptr[i]` is equal to `*(ptr + i)`

`address(ptr + i) = address(ptr) + (sizeof(T) * i)`

```cpp
int array[4] = {1, 2, 3, 4};
cout << array[1];       // print 2
cout << *(array + 1);   // print 2
cout << array;          // print 0xFFFAFFF2
cout << array + 1;      // print 0xFFFAFFF6!!
int* ptr = array + 2;
cout << ptr[-1];        // print 2
```

## Dangling pointers
### bad code
1. Local Variable Going Out of Scope
    ```cpp
    int* badFunc() {
        int x = 42;   // local variable
        return &x;    // returns address of a variable that will be destroyed
    }

    int main() {
        int* p = badFunc(); // dangling pointer
        cout << *p << endl; // undefined behavior
    }
    ```
2. Deleting Memory But Still Using Pointer
    ```cpp
    int main() {
        int* ptr = new int(10);
        delete ptr;      // memory is freed
        cout << *ptr;    // dangling pointer access → UB
    }
    ```
3. Double Delete
    ```cpp
    int* ptr = new int(5);
    delete ptr;
    delete ptr;  // undefined behavior (dangling pointer reused)
    ```
### how to prevent
1. Set pointer to `nullptr` after deletion
    ```cpp
    int* ptr = new int(5);
    delete ptr;
    ptr = nullptr;   // safe, cannot dereference
    ```
2. Avoid returning addresses of local variables
    ```cpp
    int goodFunc() {
        int x = 42;
        return x;   // safe, copy is returned
    }
    ```
3. Use Smart Pointers (`std::unique_ptr`, `std::shared_ptr`)
    ```cpp
    #include <memory>
    #include <iostream>
    using namespace std;

    int main() {
        unique_ptr<int> p = make_unique<int>(42);
        cout << *p << endl;  // automatically deleted when out of scope
    }
    ```
4. Use References Instead of Pointers (when ownership isn’t needed)
    ```cpp
    void printValue(const int& ref) {
        cout << ref << endl;
    }
    ```

* Avoid raw new / delete → prefer smart pointers.
* Initialize pointers (nullptr), don’t leave them uninitialized.
* Don’t return addresses/references to locals.