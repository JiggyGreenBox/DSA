Here is a summary of **Lambdas** and **`std::function`** with snippets, ready for your notes. 📝

-----

## 💡 Summary: Lambdas vs. `std::function`

The core distinction is that a **Lambda** is the actual *callable object* (an anonymous class), whereas **`std::function`** is a *type-erased container* used to store or pass any callable object (including a lambda) with a specific, known signature.

| Feature | Lambda (The Object) | `std::function` (The Wrapper) |
| :--- | :--- | :--- |
| **Type** | Unique, anonymous **closure class**. | Known, standard library template (e.g., `std::function<int(int)>`). |
| **Purpose** | Define **inline, disposable code** or **stateful callbacks** (via captures). | Provide a **uniform interface** for any callable (function pointer, lambda, functor) with a given signature. |
| **Overhead** | **Zero** overhead when used with `auto` (often inlined by the compiler). | **Small runtime overhead** (due to type erasure and virtual dispatch). |
| **Usage** | Use **`auto`** for storing/passing (best performance). | Use when storing different callables in a container or passing as a predictable parameter type. |

-----

## 1\. Lambdas (The Callable)

A lambda creates a unique, anonymous class instance (the closure object) that executes code.

### A. Non-Capturing Lambda (Decays to Function Pointer)

This lambda is stateless and has the least overhead. Its type can convert to a raw function pointer.

```cpp
// 1. Declaration using auto (best practice)
auto add = [](int a, int b) { 
    return a + b; 
};

// 2. Can decay to a raw function pointer if non-capturing
int (*add_ptr)(int, int) = add; 

// Usage:
int result = add(5, 7); // result = 12
```

### B. Capturing Lambda (Requires `auto` or `std::function`)

This lambda holds state (variables captured from the local scope) and **cannot** decay to a function pointer.

```cpp
int offset = 10;
int factor = 2;

// Captures 'offset' by value, 'factor' by reference
auto calculate = [offset, &factor](int x) { 
    factor += 1; // Modifies the local 'factor' variable
    return (x + offset) * factor; 
};

// Usage:
int final_val = calculate(10); // final_val = (10 + 10) * 3 = 60 
// factor is now 3
```

-----

## 2\. `std::function` (The Uniform Wrapper)

`std::function` is a template class that stores any callable object (lambda, free function, etc.) whose signature matches the template arguments.

### A. Basic Signature Pattern

The pattern is always `std::function<Return_Type(Param1_Type, Param2_Type, ...)>`.

```cpp
// Stores a callable that returns an int and takes two ints.
std::function<int(int, int)> operation; 

// 1. Assign a Lambda
operation = [](int a, int b) { return a * b; };

// 2. Assign a Free Function (if defined)
// int subtract(int a, int b) { return a - b; }
// operation = subtract; 

// Usage:
int output = operation(4, 5); // output = 20
```

### B. Usage in Classes (Callback Pattern)

`std::function` is ideal for defining flexible interfaces and callbacks.

```cpp
class Logger {
public:
    // A function that stores any callable with the signature void(const std::string&)
    std::function<void(const std::string&)> log_callback;

    void log(const std::string& msg) {
        if (log_callback) {
            log_callback("LOG: " + msg);
        }
    }
};

// --- Main Usage ---
Logger system_logger;

// Set the callback using a lambda that prints to cerr
system_logger.log_callback = [](const std::string& full_msg) {
    std::cerr << "ERR: " << full_msg << "\n";
};

// Calling the function calls the stored lambda
system_logger.log("System initialized."); 
// Output: ERR: LOG: System initialized.
```

---

Absolutely\! Using `std::function` to store or pass callable objects (like lambdas) is a crucial pattern in modern C++. It provides a **uniform, type-erased wrapper** for anything that can be called like a regular function.

Here are more examples demonstrating different return types, argument types, and its use in containers and classes.

-----

## 1\. Simple Arithmetic Examples (Different Signatures)

These examples show how to define `std::function` for various return and argument types.

| Goal | Code Example |
| :--- | :--- |
| **No Return/No Args** | `std::function<void()> say_hello = []() { std::cout << "Hello!\n"; };` |
| **Floating Point Math** | `std::function<double(double, double)> divide = [](double a, double b) { return a / b; };` |
| **Capture Local Variable** | `int offset = 10; std::function<int(int)> add_offset = [offset](int x) { return x + offset; };` |
| **Boolean Predicate** | `std::function<bool(int)> is_even = [](int n) { return n % 2 == 0; };` |

-----

## 2\. Using `std::function` in Data Structures (Containers)

This is a common use case: storing a collection of actions or callbacks with the same signature.

```cpp
#include <vector>
#include <functional> // Required for std::function

// Define a type for a function that takes an int and returns void
using Action = std::function<void(int)>;

int main() {
    std::vector<Action> actions;
    int multiplier = 5;

    // Add a lambda that prints the square of the number
    actions.push_back([](int n) { 
        std::cout << "Squared: " << n * n << "\n"; 
    });

    // Add a lambda that captures 'multiplier' and prints the product
    actions.push_back([multiplier](int n) { 
        std::cout << "Product: " << n * multiplier << "\n"; 
    });

    // Execute all stored actions
    for (const auto& action : actions) {
        action(4);
    }
}
```

-----

## 3\. Using `std::function` in Class Interfaces (Callbacks)

This is the canonical way to implement a **Callback** or **Strategy** pattern without using abstract classes.

```cpp
#include <functional>

class Processor {
private:
    // Stores the processing logic as a callable object
    std::function<int(int)> processing_logic; 

public:
    // Setter method to assign the specific logic
    void set_logic(std::function<int(int)> logic) {
        processing_logic = logic;
    }

    // Executes the stored logic
    int process(int value) {
        if (processing_logic) {
            return processing_logic(value);
        }
        return value;
    }
};

// --- Usage ---
int main() {
    Processor p;

    // Use a lambda for logic: double the input
    p.set_logic([](int x) { return x * 2; });
    std::cout << "Result 1: " << p.process(10) << "\n"; // Output: 20

    // Change the logic: add 5 to the input
    p.set_logic([](int x) { return x + 5; });
    std::cout << "Result 2: " << p.process(10) << "\n"; // Output: 15
}
```