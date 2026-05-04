# Singleton design pattern
```sh
# to compile mutltiple files
g++ -o singleton *.cpp
```

```sh
# static variables
# it gets allocated for the lifetime of the program
# Even if the function is called multiple times, space for the static variable is allocated only once and the value of the variable in the previous call gets carried through the next function call.

# https://www.geeksforgeeks.org/cpp/static-keyword-cpp/


# https://stackoverflow.com/questions/15235526/the-static-keyword-and-its-various-uses-in-c

static int x; //internal linkage
              //non-static storage - each translation unit will have its own copy of x
              //NOT A TRUE GLOBAL!

int y;        //static storage duration (can be used with extern)
              //actual global
              //external linkage
struct X
{
   static int x;     //static storage duration - shared between class instances 
};

void foo()
{
   static int x;     //static storage duration - shared between calls
}

```

```cpp
// ================================================
// worst case
// raw pointer
// ================================================
static Logger* instance = nullptr;
static Logger* getInstance() {
    if (!instance) instance = new Logger();
    return instance;
}
// Lifetime management is manual (you might leak it or forget to free).
// nullptr checks everywhere.
// Caller might think they need to delete it.
// Feels like Java/C# style, not idiomatic modern C++.
```

```cpp
// ================================================
// Better: Reference-returning singleton
// ================================================
class Logger {
private:
    static Logger instance;   // declared inside class
    Logger() {}
public:
    static Logger& getInstance() {
        return instance;      // returns the static object
    }
};
Logger Logger::instance;      // defined outside class
// The singleton is a real object, no heap allocation.
// Always valid, never nullptr.
// No ownership confusion.
// Access is clean: Logger::getInstance().log("msg");

// Here the singleton object is a class-level static member.
// Lifetime: whole program (static storage).
// Access: via reference (Logger&).
// This works, but you must provide an out-of-class definition (Logger Logger::instance;) in a .cpp file, or you’ll get linker errors.
```

```cpp
// ================================================
// Best: Meyers Singleton
// ================================================
class Logger {
private:
    Logger() {}
public:
    static Logger& getInstance() {
        static Logger instance;  // local static
        return instance;
    }
};

// Thread-safe since C++11.
// No leaks, no manual cleanup.
// Lifetime automatically tied to program runtime.
// Short, clear, idiomatic.

// Here the singleton object is a function-local static variable.
// Lifetime: whole program (static storage).
// Access: via reference (Logger&).
// No need for a separate definition in a .cpp file.
// Since C++11, initialization is guaranteed to be thread-safe.

```

#### 🔑 So are they the same?

* **Both return a reference** → the *usage* is identical:

  ```cpp
  Logger& log = Logger::getInstance();
  log.log("message");
  ```

* **Difference is in where the object lives**:

  * *Reference singleton*: static member, defined once in a `.cpp`.
  * *Meyers singleton*: static local variable inside the getter.

* **Meyers is preferred** because:

  * Simpler, no extra definition needed.
  * Thread-safe initialization guaranteed since C++11.
  * Clearer encapsulation (object can only ever be accessed through `getInstance()`).

* Meyers in my own language
  * static member functions and variables - belongs to the class not the objects
  * static variables inside a function - only visible to that function, gets carried forward in multiple calls
  * simplifies thread checks and null checks

---